#pragma once

#include <Dragon/Config.h>

#include <Dragon/Generic/Serialization/ISerializable.h>
#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Serialization/OutStream.h>

#include <Dragon/Generic/Handle.h>

#include <Dragon/Generic/StringHash.h>

#include <EASTL/vector.h>

namespace dragon
{
	using ComponentId = EntitySize;

	template<typename Component>
	ComponentId GetComponentIdentifier()
	{
		static_assert(false, "Component has not been registered. "__FUNCSIG__);
	}

#define REGISTER_COMPONENT(COMPONENT)							\
	template<>													\
	ComponentId dragon::GetComponentIdentifier<COMPONENT>()		\
	{															\
		return #COMPONENT##_hash64;								\
	}															

	/// This is the public interface for the ComponentSet, This interface should allow scripts to access anything through ids only.
	/// Which then enables us to not require the need of a Component Factory.
	class IComponentSet : public ISerializable
	{
	public:
		using Entity = Handle<EntitySize>;
		using Entities = eastl::vector<Entity>;

		// Inherited via ISerializable
		virtual void Serialize(OutStream& out) = 0;
		virtual void Deserialize(InStream& in) = 0;

		virtual void Add(Entity entity) = 0;
		virtual void Remove(Entity entity) = 0;
		virtual bool Contains(Entity entity) = 0;

		virtual void Clear() = 0;

		virtual Entities::iterator begin() = 0;
		virtual Entities::iterator end() = 0;
		virtual Entities::const_iterator cbegin() = 0;
		virtual Entities::const_iterator cend() = 0;

		// Create
		virtual void Clone(Entity original, Entity clone) = 0;

		virtual void Reserve(size_t Size) = 0;
		virtual size_t Size() const = 0;
	};

	// The component set must care about versioning of entities.
	// The only way to remove a component is to use the "current" correct entity version.
	// This means that the EntityManager must always "give" the correct entity version to remove/get the correct information.
	template<typename Component>
	class ComponentSet final : public IComponentSet
	{
		Entities m_sparse;
		Entities m_entities;

		using Components = eastl::vector<Component>;
		Components m_components;

		size_t m_size;

	public:

		Entities::iterator begin() final override { return m_entities.begin(); }
		Entities::iterator end() final override { return m_entities.end(); }
		Entities::const_iterator cbegin() final override { return m_entities.cbegin(); }
		Entities::const_iterator cend() final override { return m_entities.cend(); }

		ComponentSet()
			: m_size(0)
		{}

		void Add(Entity entity) final override
		{
			Add(entity, Component());
		}

		void Add(Entity entity, const Component& component)
		{
			Emplace(entity, component);
		}

		template<typename... Args>
		void Emplace(Entity entity, Args... args)
		{
			size_t entityIndex = (size_t)entity.GetId();
			if (entityIndex >= m_sparse.size())
				m_sparse.resize(entityIndex + 1, Entity::Invalid);

			if (m_sparse[entityIndex].IsValid())
			{
				DWARN("Overriding a valid entity component at %u", entityIndex);
			}

			m_entities.emplace_back(entity);
			m_components.emplace_back(std::forward<Args>(args)...);
			m_sparse[entityIndex] = m_entities.size() - 1;

			// Increment Size
			++m_size;
		}

		void Clear() final override
		{
			m_entities.clear();
			m_components.clear();
			m_sparse.clear();
		}

		// TODO: assert(entity.GetVersion() == m_entities[m_sparse[entity.GetId()].GetVersion())
		void Remove(Entity entity) final override
		{
			// TODO: Possibly remove the actual components from the set or atleast invalidate them?

			m_sparse[entity.GetId()].Invalidate();

			// Decrement size
			--m_size;
		}

		// TODO: assert(entity.GetVersion() == m_entities[m_sparse[entity.GetId()].GetVersion())
		bool Contains(Entity entity) final override
		{
			return m_sparse[entity.GetId()].IsValid();
		}

		// TODO: assert(entity.GetVersion() == m_entities[m_sparse[entity.GetId()].GetVersion())
		const Component& GetComponent(Entity entity) const
		{
			assert(entity.IsValid());

			size_t entityIndex = (size_t)entity.GetId();
			size_t index = m_sparse[entityIndex].GetId();

			return m_components[index];
		}

		// TODO: assert(entity.GetVersion() == m_entities[m_sparse[entity.GetId()].GetVersion())
		const Component& operator[](Entity entity) const { return GetComponent(entity); }

		// TODO: assert(entity.GetVersion() == m_entities[m_sparse[entity.GetId()].GetVersion())
		void Clone(Entity original, Entity clone) final override
		{
			Emplace(clone, GetComponent(original));
		}

		void Serialize(OutStream& out) final override
		{
			if constexpr (is_serializable_v<const Component&>)
			{
				// Count
				size_t count = m_components.size();
				out.Serialize(count);

				DLOG("Serializing %u Components : " __FUNCSIG__, count);

				// Component Data
				for (size_t i = 0; i < count; ++i)
				{
					out.Serialize(m_entities[i].m_handle);
					out.Serialize<const Component&>(m_components[i]);
				}
			}
		}

		void Deserialize(InStream& in) final override
		{
			if constexpr (is_deserializable_v<Component>)
			{
				// Count
				size_t count = in.Deserialize<size_t>();
				Reserve(count);

				DLOG("Deserializing %u Components : " __FUNCSIG__, count);

				// Component Data
				for (size_t i = 0; i < count; ++i)
				{
					EntitySize entity = in.Deserialize<EntitySize>();
					Component component = in.Deserialize<Component>();

					Emplace(entity, component);
				}
			}
		}

		void Reserve(size_t Size) final override
		{
			m_components.reserve(Size);
			m_entities.reserve(Size);
		}

		size_t Size() const final override { return m_size; }
	};

}
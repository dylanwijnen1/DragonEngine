#include "Scene.h"

#include <Dragon/Application/Debugging/Debug.h>

#include <Dragon/Generic/Serialization/OutStream.h>
#include <Dragon/Generic/Serialization/InStream.h>

#include <Box2D/Box2D.h>
#include <Dragon/Physics/Physics.h>

#include <EASTL/unordered_set.h>


namespace dragon
{

#pragma region Query Classes

	class AABBQuery : public b2QueryCallback
	{
		eastl::unordered_set<GameObject*> m_result;

	public:
		virtual bool ReportFixture(b2Fixture* pFixture)
		{
			GameObject* pGameObject = reinterpret_cast<GameObject*>(pFixture->GetBody()->GetUserData());
			m_result.emplace(pGameObject);
			return true;
		}

		Scene::GameObjects GetResult()
		{
			return Scene::GameObjects(m_result.begin(), m_result.end());
		}
	};

	// TODO: Implement RadiusQuery
	class RadiusQuery : public b2QueryCallback
	{
	public:
		virtual bool ReportFixture(b2Fixture* pFixture)
		{
			return false;
		}

		Scene::GameObjects GetResult() const
		{
			return Scene::GameObjects();
		}
	};

	class RayCastQuery : public b2RayCastCallback
	{

	};

#pragma endregion

	bool Scene::Init(Vector2f gravity)
	{
		m_pPhysicsWorld = new b2World(b2Vec2(gravity.x, gravity.y));

		return true;
	}

	void Scene::FixedUpdate(float dt)
	{
		m_pPhysicsWorld->Step(dt, 8, 3);

		// Iterate over all bodies.
			// Set the position of the Gameobject
	}

	void Scene::Render(RenderTarget& target)
	{

	}

	GameObject* Scene::Add(const GameObject& gameObject)
	{
		auto result = m_gameObjects.emplace(++m_nextId, gameObject);

		if (result.second)
		{
			return &(*result.first).second;
		}

		DWARN("[Scene] Unsuccesfully added the gameobject.");
		return nullptr;
	}

	GameObject* Scene::Add(GameObject&& gameObject)
	{
		auto result = m_gameObjects.emplace(++m_nextId, gameObject);

		if (result.second)
		{
			return &(*result.first).second;
		}

		DWARN("[Scene] Unsuccesfully added the gameobject.");
		return nullptr;
	}

	GameObject* Scene::Create()
	{
		//GameObject gameObjectToAdd(gameObject);
		GameObjectId id = ++m_nextId;
		auto result = m_gameObjects.emplace(id, GameObject::Create(id));

		if (result.second)
		{
			return &(*result.first).second;
		}

		DWARN("[Scene] Unsuccesfully added the gameobject.");
		return nullptr;
	}

	void Scene::Remove(GameObjectId id)
	{
		m_gameObjects.erase(id);
	}

	void Scene::Remove(GameObject* pGameObject)
	{
		m_gameObjects.erase(pGameObject->GetId());
	}

	GameObject* Scene::Get(GameObjectId id)
	{
		if (auto result = m_gameObjects.find(id); result != m_gameObjects.end())
		{
			return &((*result).second);
		}

		DWARN("[Scene] Could not find the game object with id: %i", id);

		return nullptr;
	}

	Scene::GameObjects Scene::QueryAABB(RectF aabb) const
	{
		AABBQuery query;
		m_pPhysicsWorld->QueryAABB(&query, b2::Convert(aabb));
		return query.GetResult();
	}

	Scene::GameObjects Scene::QueryRadius(Vector2f position, float radius) const
	{
		// TODO: Implement Radius Query.
		RadiusQuery query;
		//m_pPhysicsWorld->QueryAABB(&query, b2::Convert(aabb));
		return query.GetResult();
	}

	void Scene::Serialize(OutStream& out)
	{
		//TODO: Transform Serialization
		//out.Write(m_transform); || out.Write(m_transform.GetPosition()); out.Write(m_transform.GetRotation());
		out.Write(m_gameObjects.size());

		for (auto pair : m_gameObjects)
		{
			out.Write(pair.second.GetId());
			pair.second.Serialize(out);
		}
	}

	void Scene::Deserialize(InStream& in)
	{
		// TODO: Transform Deserialization
		//m_transform = 

		GameObjectId count = in.Read<GameObjectId>();

		for (GameObjectId index = 0; index < count; ++index)
		{
			GameObjectId id = in.Read<GameObjectId>();
			GameObject* pGameObject = CreateWithId(id);
			pGameObject->Deserialize(in);
		}
	}

	GameObject* Scene::CreateWithId(GameObjectId id)
	{
		auto result = m_gameObjects.emplace(id, GameObject::Create(id));
		return &(*result.first).second;
	}

}

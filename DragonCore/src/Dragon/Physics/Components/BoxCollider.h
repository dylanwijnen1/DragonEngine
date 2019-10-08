#pragma once

#include <Dragon/Physics/Components/Collider.h>
#include <Dragon/Generic/Math.h>

namespace dragon
{
	class BoxCollider : public Collider
	{
		Vector2f m_size;
		Vector2f m_offset;
		float m_angle;

	public:
		COMPONENT_ID(BoxCollider)

		BoxCollider()
			: m_size(1.f, 1.f)
			, m_offset(0.f, 0.f)
			, m_angle(0.f)
		{}

		~BoxCollider() = default;

		BoxCollider(const BoxCollider&) = default;
		BoxCollider(BoxCollider&&) = default;
		BoxCollider& operator=(const BoxCollider&) = default;
		BoxCollider& operator=(BoxCollider&&) = default;

		virtual bool PostInit() final override;
		virtual bool PostInit(Component* pComponent) final override;

		void SetWidth(float width);
		float GetWidth() const { return m_size.x; }

		void SetHeight(float height);
		float GetHeight() const { return m_size.y; }

		void SetSize(Vector2f size);
		Vector2f GetSize() const { return m_size; }

		void SetAngle(float angle);
		float GetAngle() const { return m_angle; }

		void SetOffset(Vector2f offset);
		Vector2f GetOffset() const;

	private:

		void SetBoxData();
	};
}
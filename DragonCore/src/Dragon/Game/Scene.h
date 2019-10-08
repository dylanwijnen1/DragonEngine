#pragma once

#include <Dragon/Generic/Math.h>
#include <Dragon/Game/GameObject.h>
#include <Dragon/Graphics/RenderTarget.h>

//#include <Dragon/Coroutines/CoroutineManager.h>

#include <Dragon/Generic/Serialization/ISerializable.h>

#include <EASTL/unordered_map.h>

class b2World;

namespace dragon
{
	class Scene : public ISerializable
	{
	
	private:
	
		GameObjectId m_nextId;

		using GameObjectContainer = eastl::unordered_map<GameObjectId, GameObject>;
		GameObjectContainer m_gameObjects;

		//CoroutineManager m_coroutineManager;
		b2World* m_pPhysicsWorld;


	public:
		using GameObjects = eastl::vector<GameObject*>;

		bool Init(Vector2f gravity = { 0.0f, 0.0f });

		void FixedUpdate(float dt);
		void Render(RenderTarget& target);

		//
		GameObject* Add(const GameObject& gameObject); // Spawns a clone of the gameObject.
		GameObject* Add(GameObject&& gameObject); // Spawns the gameObject.

		GameObject* Create(); // Creates an empty game object and immediatly adds it to the world.

		void Remove(GameObjectId id); // Removes a game object from the world.
		void Remove(GameObject* pGameObject); // Removes the game object from the world.

		GameObject* Get(GameObjectId id); // Gets the game object by id.

		//GameObjects GetByTag(const eastl::string& tag) const; // Gets the gameobjects that have this tag.
	
		GameObjects QueryAABB(RectF aabb) const; // Gets the gameobjects in an area, The game objects must have a RigidBody in order to be detected.
		GameObjects QueryRadius(Vector2f position, float radius) const;
		//GameObjects Raycast() const; This should be called from the camera maybe ?

#pragma region Getters / Setters

		b2World* GetPhysicsWorld() const { return m_pPhysicsWorld; }

#pragma endregion


#pragma region Networking
		
		//void SyncWorld() const; // Syncs the world with all clients.
		//void OnNetworkMessageReceived(NetworkMessage& message); // Handle network packets for the world.

#pragma endregion
		
#pragma region Serialization

		// Inherited via ISerializable
		virtual void Serialize(OutStream& out) override;

		virtual void Deserialize(InStream& in) override;

#pragma endregion

	private:
		// Used to create a gameobject with the specified identifier mainly used during Deserialization.
		GameObject* CreateWithId(GameObjectId id);


	};
}
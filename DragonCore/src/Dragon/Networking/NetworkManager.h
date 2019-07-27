#pragma once

#include <enet/enet.h>

#include <EASTL/string.h>
#include <EASTL/functional.h>

namespace dragon
{
	
	enum class NetworkRole
	{
		None,
		Host,
		Client,
	};

	class NetworkManager
	{
		using NetworkEventCallback = eastl::function<void(ENetEvent&)>;
		NetworkEventCallback m_callback;

		ENetHost* m_pHost;
		ENetPeer* m_pPeer;

		NetworkRole m_role;

	public:
		static auto& GetInstance()
		{
			static NetworkManager instance;
			return instance;
		}

		bool Init();

		bool StartHost(const eastl::string& host, short port = 0, size_t maxConnections = 16, size_t channels = 4);
		bool StartClient(size_t channels = 4);

		bool Connect(const eastl::string& host, short port = 0, size_t timeout = 5000);
		//bool ConnectAsync(const eastl::string& host, OnConnectedCallback, short port = 0, size_t timeout = 5000);

		void ProcessEvents();
		void SetCallback(NetworkEventCallback& callback) { m_callback = callback; }


	private:
		int ResolveAddress(const eastl::string& host) const;

		NetworkManager() = default;
	};

};
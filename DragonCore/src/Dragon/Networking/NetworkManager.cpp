#include "NetworkManager.h"

namespace dragon
{


	bool NetworkManager::Init()
	{
		if (enet_initialize() < 0)
		{
			//ERR("Failed to initialize the network driver.")
			return false;
		}

		return true;
	}

	bool NetworkManager::StartHost(const eastl::string& host, short port, size_t maxConnections, size_t channels)
	{
		m_role = NetworkRole::Host;
		ENetAddress address;
		
		if (host.empty())
			address.host = ENET_HOST_ANY;
		else
			address.host = ResolveAddress(host);

		address.port = port;

		m_pHost = enet_host_create(&address, maxConnections, channels, 0, 0);
		if (!m_pHost)
		{
			//ERR("Failed to create host service.");
			m_pHost = nullptr;
			return false;
		}

		return true;
	}

	bool NetworkManager::StartClient(size_t channels)
	{
		m_role = NetworkRole::Client;
		
		m_pHost = enet_host_create(nullptr, 1, channels, 0, 0);
		if (!m_pHost)
		{
			//ERR("Failed to create host service.");
			m_pHost = nullptr;
			return false;
		}

		return true;
	}

	bool NetworkManager::Connect(const eastl::string& host, short port, size_t timeout)
	{
		ENetAddress address;
		address.host = ResolveAddress(host);
		address.port = 1234;

		// Initiate the connection, allocating the two channels 0 and 1.
		m_pPeer = enet_host_connect(m_pHost, &address, 2, 0);
		if (!m_pPeer)
		{
			//ERR("No available peers for initiating the connection")
			return false;
		}

		// Wait up to [timeout] seconds for the connection attempt to succeed.
		ENetEvent ev;
		if (enet_host_service(m_pHost, &ev, (enet_uint32)timeout) > 0 && ev.type == ENET_EVENT_TYPE_CONNECT)
		{
			//puts("Connection to some.server.net:1234 succeeded.");
		}
		else
		{
			enet_peer_reset(m_pPeer);
			//puts("Connection to some.server.net:1234 failed.");
			return false;
		}

		return true;
	}

	void NetworkManager::ProcessEvents()
	{
		// TODO: Transform ENetEvent into NetworkEvent
		//struct NetworkEvent
		//{
		//	const char* data;
		//	unsigned int dataLen;
		//	//IStream dataStream;
		//};

		ENetEvent ev;
		while (enet_host_service(m_pHost, &ev, 0) > 0)
		{
			m_callback(ev);
		}
	}

	int NetworkManager::ResolveAddress(const eastl::string& host) const
	{
		ENetAddress address;
		address.host = 0;
		enet_address_set_host(&address, host.c_str());
		return address.host;
	}

}

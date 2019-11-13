#pragma once

#include <Dragon/Application/Debugging/Debug.h>
#include <Dragon/Generic/Handle.h>

#include <EASTL/unordered_set.h>
#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>

namespace dragon
{

	template<typename Data>
	class DirectedGraph
	{
	public:
		struct Vertex
		{
		public:
			Data m_data;
			Handle m_handle;
			Vertex(const Data& data, Handle handle) : m_data(data), m_handle(handle) {}
			Vertex(Data&& data, Handle handle) : m_data(std::move(data)), m_handle(handle) {}
		};

	private:

		using Connections = eastl::unordered_set<Handle>;
		using AdjacencyList = eastl::unordered_map<size_t, Connections>;
		AdjacencyList m_adjacencyList;

		using Vertices = eastl::vector<Vertex>;
		Vertices m_vertices;

		eastl::vector<Handle> m_freeList;

	public:

		DirectedGraph() = default;

		DirectedGraph(eastl::vector<Data>&& datas, eastl::vector<Connections>&& edges)
		{
			// Add the data and create their id's
			for (auto data : datas)
			{
				Emplace(data);
			}

			// Set the connections using the given id's
			for (size_t i = 0; i < edges.size(); ++i)
			{
				m_adjacencyList[i] = eastl::move(edges[i]);
			}
		}

		// Note: Connections will still exist.
		void ReuseVertex(Handle handle)
		{
			// Add to free list
			m_freeList.emplace_back(handle);
		}

		void Erase(Handle handle)
		{
			size_t index = handle.GetId();

			// Add to free list
			m_freeList.emplace_back(handle);
			
			// Clear all its edges
			m_adjacencyList[index].clear();

			// Remove all edges leading to the node.
			for (auto& connections : m_adjacencyList)
			{
				connections.second.erase(index);
			}
		}

		Handle Add(const Data& data)
		{
			return Emplace(data);
		}

		template<typename... Args>
		Handle Emplace(Args&& ... args)
		{
			Handle handle = NextId();

			size_t index = handle.GetId();
			if (index >= m_vertices.size())
			{
				// New ID
				m_adjacencyList.emplace(index, Connections());
				m_vertices.emplace_back(Data{ eastl::forward<Args>(args)... }, handle);
			}
			else
			{
				// Recycled ID, Move assign.
				m_adjacencyList[index].clear();
				m_vertices[index] = { { args... }, handle };
			}

			// Create's the adjacency list if it doesn't exist yet. Clears no matter what. Probably not the best way but simplest.

			return handle;
		}

		void AddEdge(Handle from, Handle to)
		{
			auto result = m_adjacencyList.find(from.GetId());
			if (result != m_adjacencyList.end())
			{
				result->second.emplace(to);
			}
			else
				DWARN("DirectedGraph::AddEdge, Adding edge from an unknown node.");
		}

		void AddEdge(const Vertex& from, const Vertex& to)
		{
			auto result = m_adjacencyList.find(from.m_handle.GetId());
			if (result != m_adjacencyList.end())
				(*result).second.emplace(to.m_handle);
		}

		const Vertices& GetVertices() const { return m_vertices; }
		size_t VertexCount() const { return m_vertices.size(); }

		const Connections* GetAdjacentNodes(Handle handle) const
		{
			uint64_t index = handle.GetId();
			auto result = m_adjacencyList.find(index);

			if (result != m_adjacencyList.end())
			{
				return result->second;
			}

			assert(result != m_adjacencyList.end());
			return nullptr;
		}

		const Vertex& operator[](Handle handle) const
		{
			return m_vertices[handle.GetId()];
		}

		Vertex& operator[](Handle handle)
		{
			return m_vertices[handle.GetId()];
		}

		void Splice(Handle nodeToReplace, const DirectedGraph& sub, Handle entrance, Handle exit)
		{
			uint64_t replaceIndex = nodeToReplace.GetId();

			// Calculate incoming nodes.
			Connections inList;

			for (auto& pair : m_adjacencyList)
			{
				auto& connections = pair.second;

				auto result = connections.find(replaceIndex);
				if (result != connections.end())
				{
					// Add the connection to our in-list
					inList.emplace(*result);

					// Remove the connection from the adjacency set of this node.
					connections.erase(replaceIndex);
				}
			}

			// Copy the outgoing nodes.
			Connections outList(m_adjacencyList[replaceIndex]);

			// Clear outgoing nodes
			m_adjacencyList[replaceIndex].clear();

			// Reuse the node (Don't destroy takes extra time we handle reconstruction of edges in here anyway)
			ReuseVertex(nodeToReplace);

			// Clone the entire sub graph into our graph and map their old id's to the new id's
			eastl::unordered_map<size_t, size_t> nodeMap;

			// Clone nodes
			for (const auto& vertex : sub.m_vertices)
			{
				Handle newHandle = Add(vertex.m_data);
				nodeMap.emplace(vertex.m_handle.GetId(), newHandle.GetId());
			}

			// Clone edges
			for (const auto& connections : sub.m_adjacencyList)
			{
				for (Handle handle : connections.second)
				{
					Handle newFrom = nodeMap[connections.first];
					Handle newTo = nodeMap[handle.GetId()];
					AddEdge(newFrom, newTo);
				}
			}

			// Link the incoming and outgoing nodes.
			for (Handle handle : inList)
				AddEdge(handle, nodeMap[entrance.GetId()]);

			for (Handle handle : outList)
				AddEdge(nodeMap[exit.GetId()], handle);
		}

		// Path:BFS(start, goal) const

		// Path:DFS(start, goal) const

		// Path:AStar(start, goal, heuristic) const

	private:

		Handle NextId()
		{
			Handle handle = 0; // Invalid handle.

			// See if we have any IDs on the free list.
			if (m_freeList.size() > 0)
			{
				handle = m_freeList.back();
				m_freeList.pop_back();
			}
			// New ID
			else
			{
				handle = m_vertices.size();
			}

			handle.Increment();
			return handle;
		}

	};

}
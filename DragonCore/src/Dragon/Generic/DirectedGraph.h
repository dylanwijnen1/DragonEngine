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
			Vertex(Data&& data, Handle handle) : m_data(data), m_handle(handle) {}
		};

	private:

		using Connections = eastl::unordered_set<Handle>;
		using AdjacencyList = eastl::unordered_map<uint64_t, Connections>;
		AdjacencyList m_adjacencyList;

		using Vertices = eastl::vector<Vertex>;
		Vertices m_vertices;

		eastl::vector<Handle> m_freeList;

	public:

		DirectedGraph() = default;

		DirectedGraph(std::initializer_list<std::pair<Data, Connections>> data)
		{
			for (auto pair : data)
			{
				auto newId = Emplace(pair.first);
				m_adjacencyList[newId.GetId()] = std::move(pair.second);
			}
		}

		// Note: Connections will still exist.
		void Dereference(Handle handle)
		{
			// Add to free list
			m_freeList.emplace_back(handle);
		}

		void Erase(Handle handle)
		{
			uint64_t index = handle.GetId();

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

			uint64_t index = handle.GetId();
			if (index >= m_vertices.size())
			{
				// New ID
				m_adjacencyList[index]
				m_vertices.emplace_back(Data{ eastl::forward<Args>(args)... }, handle);
			}
			else
			{
				// Recycled ID, Move assign.
				m_vertices[index] = { { args... }, handle };
				m_adjacencyList[index].clear();
			}

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

		const Connections& GetAdjacentNodes(Handle handle) const
		{
			uint64_t index = handle.GetId();
			auto result = m_adjacencyList.find(index);
			if (result != m_adjacencyList.end())
			{
				return result->second;
			}

			return Connections(); // Empty
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

			for (auto& connections : m_adjacencyList)
			{
				auto result = m_adjacencyList.find(replaceIndex);
				if (result != m_adjacencyList.end())
				{
					// Add the connection to our in-list
					inList.emplace(result->first);

					// Remove the connection from the adjacency set of this node.
					connections.second.erase(replaceIndex);
				}
			}

			// Copy the outgoing nodes.
			Connections outList(m_adjacencyList[replaceIndex]);

			// Clear outgoing nodes
			m_adjacencyList[replaceIndex].clear();

			// Dereference the node (Don't destroy takes extra time we handle reconstruction of edges in here anyway)
			Dereference(nodeToReplace);

			// Clone the entire sub graph into our graph and map their old id's to the new id's
			eastl::unordered_map<uint64_t, uint64_t> nodeMap;

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
					uint64_t newFrom = nodeMap[connections.first];
					uint64_t newTo = nodeMap[handle.GetId()];
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
#ifndef CONTIGPATH_H
#define CONTIGPATH_H

#include "DirectedGraph.h" // for LinearNumKey
#include <iostream>

struct MergeNode
{
	LinearNumKey id;
	bool isRC;
	
	void flip() { isRC = (isRC) ? 0 : 1; }

	bool operator <(const MergeNode& o) const
	{
		return id != o.id ? id < o.id : isRC < o.isRC;
	}

	friend std::ostream& operator<<(std::ostream& out,
			const MergeNode& o)
	{
		return out << o.id << ',' << o.isRC;
	}

	friend std::istream& operator>>(std::istream& in, MergeNode& o)
	{
		char c;
		in >> o.id >> c >> o.isRC;
		if (in.good())
			assert(c == ',');
		return in;
	}
};

class ContigPath
{
	public:
		// Add a node to this path
		void appendNode(const MergeNode& mn);
		
		// prepend a path
		void prependPath(const ContigPath& other);
		
		// append a path
		void appendPath(const ContigPath& other);
		
		// Get the number of nodes in the path
		size_t getNumNodes() const { return m_path.size(); }
		
		// Get the node with a specified index
		MergeNode& getNode(size_t idx)
		{
			assert(idx < m_path.size());
			return m_path[idx];
		}
		
		// Get the node with a specified index
		const MergeNode& getNode(size_t idx) const
		{
			assert(idx < m_path.size());
			return m_path[idx];
		}

		// reverse the path
		void reverse(bool flipNodes);
		
		// Extract a subset from the path
		ContigPath extractNodes(size_t start, size_t end);

		bool operator <(const ContigPath& o) const
		{
			return m_path < o.m_path;
		}

		// Insertion/Extraction operators
		friend std::ostream& operator<<(std::ostream& out, const ContigPath& object);
		friend std::istream& operator>>(std::istream& in, ContigPath& object);

	private:
		std::vector<MergeNode> m_path;
};

#endif

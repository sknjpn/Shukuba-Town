#include "Junction.h"
#include "Path.h"
#include "Node.h"

namespace skn
{
	Junction::Junction(Node* node)
		: Transform(node->get_position())
		, m_node(node)
		, m_path(nullptr)
		, m_t(0)
	{
	
	}

	Junction::Junction(Path* path, double t)
		: Transform(path->get_from()->get_position() + (path->get_to()->get_position() - path->get_from()->get_position()).setLength(t))
		, m_node(nullptr)
		, m_path(path)
		, m_t(t)
	{
	
	}
}
#include "Junction.h"

namespace skn
{
	Junction::Junction(Node* node)
		: m_node(node)
		, m_path(nullptr)
		, m_t(0)
	{
	}
	Junction::Junction(Path* path, double t)
		: m_node(nullptr)
		, m_path(path)
		, m_t(t)
	{
	}
}
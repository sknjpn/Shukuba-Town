#pragma once

#include "Transform.h"

namespace skn
{
	class Node;
	class Path;

	class Junction
		: public Transform
	{
		Node*	m_node;
		Path*	m_path;
		double	m_t;

	public:
		Junction(Node* node);
		Junction(Path* path, double t);
	};
}
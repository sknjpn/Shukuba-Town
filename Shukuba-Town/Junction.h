#pragma once

#include "Transform.h"

namespace skn
{
	class Path;

	class Junction
		: public Transform
	{
		Path*	m_path;
		double	m_t;

	public:
		Junction(Path* path, double t);
	};
}
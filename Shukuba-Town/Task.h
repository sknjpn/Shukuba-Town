#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Agent;

	class Task
		: public Uncopyable
	{
	public:
		virtual	~Task() = default;

		virtual bool	update(Agent* agent) = 0;
	};
}
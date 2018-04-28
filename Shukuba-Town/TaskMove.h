#pragma once

#include "Task.h"
#include "Transform.h"

namespace skn
{
	class TaskMove
		: public Task
	{
		Position	m_target;

		std::vector<Position>	waypoints;

	public:
		TaskMove(const Position& target);

		bool	update(Agent* agent) override;
	};
}
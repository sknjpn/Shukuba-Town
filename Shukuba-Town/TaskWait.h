#pragma once

#include "Task.h"

namespace skn
{
	class TaskWait
		: public Task
	{
		double	m_time;

	public:
		TaskWait(double time);

		bool	update(Agent* agent) override;
	};
}
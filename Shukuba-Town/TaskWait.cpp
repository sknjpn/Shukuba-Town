#include "TaskWait.h"

#include "Agent.h"

namespace skn
{
	TaskWait::TaskWait(double time)
		: m_time(time)
	{

	}

	bool TaskWait::update(Agent* agent)
	{
		m_time -= agent->get_power();

		return agent->wait(m_time);
	}
}
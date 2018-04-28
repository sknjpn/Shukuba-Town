#include "TaskMove.h"

#include "Agent.h"

namespace skn
{
	TaskMove::TaskMove(const Position& target)
		: m_target(target)
	{

	}

	bool TaskMove::update(Agent* agent)
	{
		return agent->move(m_target);
	}
}
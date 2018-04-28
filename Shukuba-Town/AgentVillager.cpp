#include "AgentVillager.h"

#include "Village.h"

#include "TaskMove.h"
#include "TaskWait.h"

namespace skn
{
	AgentVillager::AgentVillager()
		: m_job(nullptr)
	{

	}

	void AgentVillager::behave()
	{
		add_task(new TaskMove(get_position() + s3d::RandomVec2(100.0)));
		add_task(new TaskWait(0.1));
	}
}
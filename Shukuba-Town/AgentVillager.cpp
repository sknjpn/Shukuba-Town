#include "AgentVillager.h"

#include "Village.h"

#include "Job.h"

#include "TaskMove.h"
#include "TaskWait.h"

namespace skn
{
	void AgentVillager::behave()
	{
		if (m_job != nullptr)
		{
			m_job->work();
		}
		else
		{
			add_task(new TaskMove(get_position() + s3d::RandomVec2(100.0)));
			add_task(new TaskWait(0.1));
		}
	}
}
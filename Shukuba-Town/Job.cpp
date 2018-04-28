#include "Job.h"

namespace skn
{
	Job::Job()
		: m_agent(nullptr)
	{

	}

	Agent* Job::get_agent() const
	{
		return m_agent;
	}

	void Job::work()
	{

	}
}
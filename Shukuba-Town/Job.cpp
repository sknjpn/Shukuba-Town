#include "Job.h"

namespace skn
{
	Job::Job()
		: m_user(nullptr)
		, m_owner(nullptr)
	{

	}

	Agent* Job::get_user() const
	{
		return m_user;
	}

	Building * Job::get_owner() const
	{
		return m_owner;
	}

	void Job::work()
	{

	}
}
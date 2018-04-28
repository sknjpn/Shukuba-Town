#include "Job.h"

namespace skn
{
	Job::Job(Building* owner)
		: m_user(nullptr)
		, m_owner(owner)
	{

	}

	void Job::assign(Agent* user)
	{
		m_user = user;
	}

	Agent* Job::get_user() const
	{
		return m_user;
	}

	Building* Job::get_owner() const
	{
		return m_owner;
	}

	void Job::work()
	{

	}
}
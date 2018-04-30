#pragma once

#include "Agent.h"

namespace skn
{
	class Job;

	class AgentVillager
		: public Agent
	{
		Job*	m_job;

	public:
		AgentVillager();

		void	behave() override;
	};
}
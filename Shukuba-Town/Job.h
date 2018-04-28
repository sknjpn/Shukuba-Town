#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Agent;

	class Job
		: Uncopyable
	{
		Agent*	m_agent;

	public:
		Job();
		virtual ~Job() = default;

		Agent* get_agent() const;

		virtual void	work();
	};
}
#pragma once

#include "Uncopyable.h"
#include "Building.h"

namespace skn
{
	class Agent;
	class Building;

	class Job
		: Uncopyable
	{
		Agent*		m_user;
		Building*	m_owner;

	public:
		Job(Building* owner);
		virtual ~Job() = default;

		void		assign(Agent* user);

		Agent*		get_user() const;
		Building*	get_owner() const;

		virtual void	work();
	};
}
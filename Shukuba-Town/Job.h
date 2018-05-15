#pragma once

namespace skn
{
	class Agent;
	class Building;

	class Job
		: public Uncopyable
	{
		Agent*		m_user;
		Building*	m_owner;

	public:
		Job(Building* owner) : m_user(nullptr), m_owner(owner) {}
		virtual ~Job() = default;

		void		assign(Agent* user) { m_user = user; }

		//getter
		Agent*		get_user() const { return m_user; }
		Building*	get_owner() const { return m_owner; }

		virtual void	work() {};
	};
}
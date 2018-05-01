#pragma once

#include "Balloon.h"
#include "Transform.h"

namespace skn
{
	class Task;

	class Agent
		: public Transform
	{
		double		m_power;
		Balloon		m_balloon;
		std::vector<Task*>	m_tasks;

	public:
		Agent(const Position& position) : Transform(position), m_power(0), m_balloon(this) {}
		virtual ~Agent() = default;

		void	add_power(double power) { m_power += power; }
		void	add_task(Task* task) { m_tasks.emplace_back(task); }

		double	get_power() const { return m_power; }

		//Task
		bool	move(const s3d::Vec2& target);
		bool	wait(double time);

		void	draw() const;
		void	update();

		virtual void	behave() = 0;
	};
}
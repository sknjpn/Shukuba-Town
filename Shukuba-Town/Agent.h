#pragma once

#include "Uncopyable.h"
#include "Balloon.h"
#include "Transform.h"

namespace skn
{
	class Task;

	class Agent
		: public Transform
	{
		double		m_power;
		s3d::Color	m_color;
		Balloon		m_balloon;
		std::vector<Task*>	m_tasks;

	public:
		Agent(const Position& position, s3d::Color color);
		virtual ~Agent() = default;

		void	add_power(double power);
		void	add_task(Task* task);

		double	get_power() const;

		const std::vector<Task*>&	get_tasks() const;

		//Task
		bool	move(const s3d::Vec2& target);
		bool	wait(double time);

		void	draw() const;
		void	update();

		virtual void	behave() = 0;
	};
}
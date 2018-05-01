#pragma once

namespace skn
{
	class Clock
	{
		double		m_speed;
		double		m_time;

	public:
		Clock() : m_speed(0), m_time(0) {}

		void		set_speed(double speed) { m_speed = speed; }
		double		get_speed() const { return m_speed; }

		void		set_time(double time) { m_time = time; }

		void		update() { m_time += m_speed; }

		s3d::String	get_time_as_string() const;
	};
}
#pragma once

namespace skn
{
	class Clock
	{
		double		m_speed;
		double		m_time;

	public:
		Clock();

		void		set_speed(double speed);
		double		get_speed() const;

		void		set_time(double time);

		void		update();

		s3d::String	get_time_as_string() const;
	};
}
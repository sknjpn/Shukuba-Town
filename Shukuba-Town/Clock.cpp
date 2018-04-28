#include "Clock.h"

namespace skn
{
	Clock::Clock()
		: m_speed(0)
		, m_time(0)
	{

	}

	void Clock::set_speed(double speed)
	{
		m_speed = speed;
	}

	double Clock::get_speed() const
	{
		return m_speed;
	}

	void Clock::set_time(double time)
	{
		m_time = time;
	}

	void Clock::update()
	{
		m_time += m_speed;
	}

	s3d::String Clock::get_time_as_string() const
	{
		auto year = int(m_time / 12.0);
		auto month = int(m_time) % 12 + 1;
		auto hour = int(m_time * 24.0) % 24;
		auto minute = int(m_time * 24.0 * 60.0) % 60;
		auto second = int(m_time * 24.0 * 60.0 * 60.0) % 60;

		return s3d::Format(
			s3d::Pad(year, { 4, U'0' }), U"�N",
			s3d::Pad(month, { 2, U'0' }), U"��",
			s3d::Pad(hour, { 2, U'0' }), U"��",
			s3d::Pad(minute, { 2, U'0' }), U"��",
			s3d::Pad(second, { 2, U'0' }), U"�b"
		);
	}
}
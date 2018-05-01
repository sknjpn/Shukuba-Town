#include "Clock.h"

namespace skn
{
	s3d::String Clock::get_time_as_string() const
	{
		auto year = int(m_time / 12.0);
		auto month = int(m_time) % 12 + 1;
		auto hour = int(m_time * 24.0) % 24;
		auto minute = int(m_time * 24.0 * 60.0) % 60;
		auto second = int(m_time * 24.0 * 60.0 * 60.0) % 60;

		return s3d::Format(
			s3d::Pad(year, { 4, U'0' }), U"”N",
			s3d::Pad(month, { 2, U'0' }), U"ŒŽ",
			s3d::Pad(hour, { 2, U'0' }), U"Žž",
			s3d::Pad(minute, { 2, U'0' }), U"•ª",
			s3d::Pad(second, { 2, U'0' }), U"•b"
		);
	}
}
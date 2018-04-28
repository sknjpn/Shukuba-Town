#pragma once

#include "Job.h"

namespace skn
{
	class JobBaker
		: public Job
	{
		s3d::Vec2 m_target;

	public:
		JobBaker(s3d::JSONValue json);

		void	work() override;
	};
}

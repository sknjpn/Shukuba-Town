#pragma once

#include "Job.h"

namespace skn
{
	class Job_Baker
		: public Job
	{
		s3d::Vec2 m_target;

	public:
		Job_Baker(Building* owner, s3d::JSONValue json);

		void	work() override;
	};
}

#pragma once

#include "Job.h"

namespace skn
{
	class JobFarmer
		: public Job
	{
		s3d::Vec2 m_target;

	public:
		JobFarmer(s3d::JSONValue json);

		void	work() override;
	};
}

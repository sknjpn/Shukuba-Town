#pragma once

#include "Job.h"

namespace skn
{
	class Job_Farmer
		: public Job
	{
		s3d::Vec2 m_target;

	public:
		Job_Farmer(Building* owner, s3d::JSONValue json);

		void	work() override;
	};
}

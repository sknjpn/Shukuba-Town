#pragma once

#include "Job.h"

class Job_Baker
	: public Job
{
	Vec2 m_target;

public:
	Job_Baker(Building* owner, JSONValue json);

	void	work() override;
};
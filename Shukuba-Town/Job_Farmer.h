#pragma once

#include "Job.h"

class Job_Farmer
	: public Job
{
	Vec2 m_target;

public:
	Job_Farmer(Building* owner, JSONValue json);

	void	work() override;
};
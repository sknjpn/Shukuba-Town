#pragma once

#include "Agent.h"

namespace skn
{
	class AgentVisitor
		: public Agent
	{
	public:
		void	behave() override;
	};
}
#pragma once

#include "Agent.h"

namespace skn
{
	class AgentPlayer
		: public Agent
	{
	public:
		void	behave() override;
	};
}
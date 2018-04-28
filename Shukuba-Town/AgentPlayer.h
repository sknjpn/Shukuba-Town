#pragma once

#include "Agent.h"

namespace skn
{
	class AgentPlayer
		: public Agent
	{
	public:
		AgentPlayer(const Position& position);

		void	behave() override;
	};
}
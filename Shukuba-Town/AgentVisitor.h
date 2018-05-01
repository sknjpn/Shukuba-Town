#pragma once

#include "Agent.h"

namespace skn
{
	class AgentVisitor
		: public Agent
	{
	public:
		AgentVisitor(const Position& position) : Agent(position) {}

		void	behave() override;
	};
}
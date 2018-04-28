#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Scene
		: Uncopyable
	{
	public:
		virtual ~Scene() = default;

		virtual void	start() = 0;
		virtual void	update() = 0;
	};
}
#pragma once

#include "Scene.h"

namespace skn
{
	class SceneGame
		: public Scene
	{
	public:
		void	start() override;
		void	update() override;
	};
}
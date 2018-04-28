#pragma once

#include "Scene.h"

namespace skn
{
	class SceneTitle
		: public Scene
	{
	public:
		void	start() override;
		void	update() override;
	};
}
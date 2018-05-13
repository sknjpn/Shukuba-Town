#pragma once

#include "Scene.h"

class Scene_Game
	: public Scene
{
public:
	void start() override;
	void update() override;
};
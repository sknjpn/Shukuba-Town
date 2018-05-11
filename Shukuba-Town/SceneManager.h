#pragma once

#include "Uncopyable.h"

class Scene;

class SceneManager
	: public Uncopyable
{
	Scene* m_scene;

public:
	static void Run(Scene* scene);
};

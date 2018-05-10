#pragma once

class Scene;

class SceneManager
{
	Scene* m_scene;

public:
	static void Run(Scene* scene);
};

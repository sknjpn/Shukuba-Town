#pragma once

class Scene;

class SceneManager
	: public Uncopyable
{
	Scene* m_scene;

public:
	static void Run(Scene* scene);
};

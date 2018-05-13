#pragma once

class Scene;

class SceneManager
	: public Uncopyable
{
	Scene* m_scene;

	static SceneManager* s_instance;

public:
	static void Run(Scene* scene);
};
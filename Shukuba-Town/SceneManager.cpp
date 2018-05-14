#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Run(Scene* scene)
{
	if (s_instance == nullptr)
	{
		s_instance = new SceneManager();
	}

	scene->start();

	while (System::Update())
	{
		scene->update();
	}
}

SceneManager* SceneManager::s_instance = nullptr;
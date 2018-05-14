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
		ClearPrint();

		scene->update();
	}
}

SceneManager* SceneManager::s_instance = nullptr;
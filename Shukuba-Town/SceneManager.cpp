#include "SceneManager.h"
#include "Scene.h"

namespace skn
{
	SceneManager& SceneManager::get_instance()
	{
		static SceneManager instance;

		return instance;
	}

	void SceneManager::run(Scene* scene)
	{
		auto& instance = get_instance();

		instance.m_scene = scene;
		instance.m_scene->start();

		while (s3d::System::Update())
		{
			s3d::ClearPrint();

			instance.m_scene->update();
		}
	}

	void SceneManager::change(Scene* scene)
	{
		auto& instance = get_instance();

		delete instance.m_scene;

		instance.m_scene = scene;
		instance.m_scene->start();
	}
}
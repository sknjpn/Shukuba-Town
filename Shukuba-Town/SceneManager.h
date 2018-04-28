#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Scene;

	class SceneManager
		: Uncopyable
	{
		Scene*	m_scene;

		SceneManager() = default;
		~SceneManager() = default;

		static SceneManager& get_instance();

	public:
		static void	run(Scene* scene);
		static void	change(Scene* scene);
	};
}
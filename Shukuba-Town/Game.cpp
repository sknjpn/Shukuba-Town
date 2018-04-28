#include "Game.h"
#include "SceneManager.h"
#include "SceneGame.h"

namespace skn
{
	Game::Game()
	{
		s3d::Window::SetTitle(U"Shukuba Town");

		//s3d::Graphics::SetFullScreen(true, s3d::Graphics::EnumOutputs().back().displayRect.size);
		s3d::Window::Resize(640, 480);

		SceneManager::run(new SceneGame());
	}
}
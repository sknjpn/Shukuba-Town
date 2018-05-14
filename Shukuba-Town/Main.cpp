#include "SceneManager.h"
#include "Scene_Game.h"

void Main()
{
	Window::SetTitle(U"Shukuba-Town");
	Window::Resize(1280, 720);

	SceneManager::Run(new Scene_Game);
}

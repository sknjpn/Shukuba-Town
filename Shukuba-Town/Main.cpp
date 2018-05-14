#include "SceneManager.h"
#include "Scene_Game.h"

void Main()
{
	SceneManager::Run(new Scene_Game);
}

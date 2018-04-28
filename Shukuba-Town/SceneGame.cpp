#include "SceneGame.h"

#include "Village.h"

namespace skn
{
	void SceneGame::start()
	{
		g_village = new Village;
	}

	void SceneGame::update()
	{
		g_village->update();
	}
}
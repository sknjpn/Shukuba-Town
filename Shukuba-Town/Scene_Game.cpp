#include "Scene_Game.h"
#include "Field.h"

void Scene_Game::start()
{
	g_field = new Field();
}

void Scene_Game::update()
{
	g_field->update();
}

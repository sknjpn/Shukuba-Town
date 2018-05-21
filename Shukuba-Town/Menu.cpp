#include "Menu.h"

#include "Button.h"
#include "Button_Building.h"
#include "Button_Road.h"
#include "Button_Quit.h"

Menu::Menu()
{
	m_buttons.emplace_back(new Button_Road(RectF(32, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(0, 0, 32, 32))));
}

Menu::~Menu()
{

}

void Menu::update()
{
	for (auto* b : m_buttons)
	{
		b->draw();
	}
}

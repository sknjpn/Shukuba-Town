#include "Menu.h"

#include "Button.h"
#include "Button_Building.h"
#include "Button_Road.h"
#include "Button_Quit.h"

Menu::Menu()
{
	for (int i = 0; i < 16; i++)
	{
		auto region = RectF(32 + i * 64, 32, 64, 64);
		auto texture = Texture(Image(U"data/menu.png").clipped(i * 32, 0, 32, 32));

		m_buttons.emplace_back(new Button_Road(region, texture));
	}
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

#include "Menu.h"

#include "Button.h"
#include "Button_Building.h"
#include "Button_Road.h"
#include "Button_Quit.h"

Menu::Menu()
{
	m_buttons.emplace_back(new Button_Road(RectF(32 + 0 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(0 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Road(RectF(32 + 1 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(1 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 2 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(2 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 3 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(3 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 4 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(4 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 5 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(5 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 6 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(6 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Quit(RectF(32 + 7 * 64, 32, 64, 64), Texture(Image(U"data/menu.png").clipped(7 * 32, 0, 32, 32))));
}

Menu::~Menu()
{

}

void Menu::update()
{
	if (MouseL.down())
	{
		for (auto* b : m_buttons)
		{
			if (b->mouse_over())
			{
				b->on_clicked();

				break;
			}
		}
	}

	for (auto* b : m_buttons)
	{
		b->draw();
	}
}

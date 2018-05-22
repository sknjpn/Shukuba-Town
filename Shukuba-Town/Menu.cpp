#include "Menu.h"

#include "Button.h"
#include "Button_Building.h"
#include "Button_Road.h"
#include "Button_Quit.h"

Menu::Menu()
{
	auto image = Image(U"data/menu.png");
	auto json = JSONReader(U"data/data.json");

	m_buttons.emplace_back(new Button_Road(RectF(32 + 0 * 64, 32, 64, 64), Texture(image.clipped(0 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Road(RectF(32 + 1 * 64, 32, 64, 64), Texture(image.clipped(1 * 32, 0, 32, 32))));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 2 * 64, 32, 64, 64), Texture(image.clipped(2 * 32, 0, 32, 32)), json[U"buildings"].arrayView()[0]));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 3 * 64, 32, 64, 64), Texture(image.clipped(3 * 32, 0, 32, 32)), json[U"buildings"].arrayView()[1]));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 4 * 64, 32, 64, 64), Texture(image.clipped(4 * 32, 0, 32, 32)), json[U"buildings"].arrayView()[2]));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 5 * 64, 32, 64, 64), Texture(image.clipped(5 * 32, 0, 32, 32)), json[U"buildings"].arrayView()[3]));
	m_buttons.emplace_back(new Button_Building(RectF(32 + 6 * 64, 32, 64, 64), Texture(image.clipped(6 * 32, 0, 32, 32)), json[U"buildings"].arrayView()[4]));
	m_buttons.emplace_back(new Button_Quit(RectF(32 + 7 * 64, 32, 64, 64), Texture(image.clipped(7 * 32, 0, 32, 32))));
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

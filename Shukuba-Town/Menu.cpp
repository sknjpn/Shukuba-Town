#include "Menu.h"

#include "Button.h"
#include "Button_Building.h"
#include "Button_Road.h"
#include "Button_Quit.h"

Menu::Menu()
{
	m_buttons.emplace_back(new Button_Road());
}

Menu::~Menu()
{
}

void Menu::update()
{
}

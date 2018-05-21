#pragma once

class Button;

class Menu
	: public Uncopyable
{
	Array<Button> m_buttons;

public:
	Menu();
	~Menu();

	void update();
};
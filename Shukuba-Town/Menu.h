#pragma once

class Button;

class Menu
	: public Uncopyable
{
	Array<Button*> m_buttons;

public:
	Menu(JSONValue json);
	~Menu();

	bool any_mouse_over() const;

	void update();
};
#pragma once

#include "Button.h"

class Button_Quit
	: public Button
{
public:
	Button_Quit(const RectF& rect, Texture texture);
	~Button_Quit();
};

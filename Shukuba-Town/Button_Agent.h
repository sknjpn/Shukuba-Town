#pragma once

#include "Button.h"

class Button_Agent 
	: public Button
{
public:
	Button_Agent(const RectF& rect, Texture texture;
	~Button_Agent();

	void on_clicked() override;
};


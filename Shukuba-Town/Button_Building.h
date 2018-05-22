#pragma once

#include "Button.h"

class Button_Building
	: public Button
{
	JSONValue	m_json;

public:
	Button_Building(const RectF& rect, Texture texture, JSONValue json);
	~Button_Building();

	void on_clicked() override;
};

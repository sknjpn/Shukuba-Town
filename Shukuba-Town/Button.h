#pragma once

class Button
	: public Uncopyable
{
	bool	m_is_selected;
	RectF	m_rect;
	Texture	m_texture;

public:
	virtual ~Button() = default;

	virtual void on_clicked() = 0;

	void	draw();
};

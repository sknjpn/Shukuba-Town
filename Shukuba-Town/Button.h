#pragma once

class Button
	: public Uncopyable
{
	bool	m_is_selected;
	RectF	m_rect;
	Texture	m_texture;

public:
	Button(const RectF& rect, Texture texture);
	virtual ~Button() = default;

	virtual void on_clicked() = 0;

	bool	mouse_over() const { return m_rect.mouseOver(); }

	void	draw();
};

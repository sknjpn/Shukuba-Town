#pragma once

class Sample
{
	bool	m_is_selected;
	Rect	m_rect;
	Texture m_texture;

public:
	Sample(const Rect& rect, Texture texture);

	bool	is_selected() const { return m_is_selected; }

	void	update();
};
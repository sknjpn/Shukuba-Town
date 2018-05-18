#pragma once

class Sample
{
	bool	m_is_selected;
	Rect	m_rect;
	Texture m_texture;

public:
	Sample(const Rect& rect, Texture texture);

	void	set_selected(bool is_selected) { m_is_selected = is_selected; }

	bool	is_left_clicked() const { return m_rect.leftClicked(); }

	void	update();

	void	draw();
};
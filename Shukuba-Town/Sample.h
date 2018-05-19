#pragma once

class Sample
	: public Uncopyable
{
	bool	m_is_selected;
	Rect	m_rect;
	Texture m_texture;

public:
	Sample(const Rect& rect, Texture texture);
	virtual ~Sample() = default;

	bool	is_selected() const { return m_is_selected; }

	void	update();
};
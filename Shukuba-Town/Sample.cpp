#include "Sample.h"

Sample::Sample(const Rect& rect, Texture texture)
	: m_rect(rect)
	, m_texture(texture)
{

}

void Sample::update()
{
	if (MouseL.down()) { m_is_selected = m_rect.leftClicked(); }

	{
		auto color = m_is_selected ? Palette::Orange : m_rect.mouseOver() ? ColorF(1.0, 0.8) : ColorF(1.0, 0.4);

		RoundRect(m_rect, 8).draw(ColorF(color, 0.5)).drawFrame(1.0, color);

		m_texture.resized(m_rect.size).draw(m_rect.pos);
	}
}

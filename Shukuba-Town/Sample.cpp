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
		auto color = m_is_selected ? Palette::Orange : Palette::White;

		RoundRect(m_rect, 8)
			.draw(m_rect.mouseOver() ? ColorF(color, 0.6) : ColorF(color, 0.3))
			.drawFrame(1.0, color);

		m_texture.resized(m_rect.size).draw(m_rect.pos);
	}
}

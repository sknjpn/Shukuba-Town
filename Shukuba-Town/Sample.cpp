#include "Sample.h"

Sample::Sample(const Rect& rect, Texture texture)
	: m_rect(rect)
	, m_texture(texture)
{

}

void Sample::update()
{
	if (!MouseL.pressed()) { m_is_selected = false; }
	if (MouseL.down()) { m_is_selected = m_rect.leftClicked(); }

	m_rect.draw(ColorF(1.0, 0.5)).drawFrame(2.0, ColorF(1.0));
}

#include "Button.h"

void Button::draw()
{
	m_texture.resized(m_rect.size).draw(m_rect.pos);
}

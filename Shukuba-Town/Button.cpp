#include "Button.h"

Button::Button(const RectF& rect, Texture texture)
	: m_is_selected(false)
	, m_texture(texture)
	, m_rect(rect)
{

}

void Button::draw()
{
	m_texture.resized(m_rect.size).draw(m_rect.pos);
}

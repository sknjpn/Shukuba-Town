#include "Balloon.h"
#include "Agent.h"

namespace skn
{
	Balloon::Balloon(Agent* agent)
		: m_font(14)
		, m_agent(agent)
		, m_text()
		, m_counter(0)
	{

	}

	void Balloon::set_text(const s3d::String& text)
	{
		m_text = text;
		m_counter = 90;
	}

	void Balloon::update()
	{
		if (m_counter > 0)
		{
			auto c1 = s3d::ColorF(s3d::Palette::White, s3d::Min(1.0, m_counter / 15.0));
			auto c2 = s3d::ColorF(s3d::Palette::Black, s3d::Min(1.0, m_counter / 15.0));
			auto drawable_text = m_font(m_text);
			auto position = m_agent->get_position().movedBy(5, -5);
			auto rect = drawable_text.boundingRect().stretched(5, 2.5).movedBy(position + s3d::Vec2(0, -25));

			s3d::Shape2D::RectBalloon(rect, position).draw(c1);

			drawable_text.drawAt(rect.center(), c2);

			m_counter--;
		}
	}
}
#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Agent;

	class Balloon
		: Uncopyable
	{
		Agent*		m_agent;
		s3d::Font	m_font;
		s3d::String m_text;
		int			m_counter;

	public:
		Balloon(Agent* agent);

		void		set_text(const s3d::String& text);

		void		update();
	};
}
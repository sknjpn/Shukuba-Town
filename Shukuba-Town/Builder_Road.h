#pragma once

#include "Builder.h"

class Node;

class Builder_Road
	: public Builder
{
	class Sample
	{
		bool	m_is_selected;

	public:
		Sample();

		void	set_selected(bool is_selected) { m_is_selected = is_selected; }

		bool	is_clicked(const Vec2& position) const;

		void	draw(const Vec2& position);
	};

	Vec2	m_from_position;
	Vec2	m_to_position;

	Sample*		m_selected_sample;
	Array<Sample*>	m_samples;

	void		set_from_position(const Vec2& position);
	void		set_to_position(const Vec2& position);

	bool		can_set() const;

public:
	Builder_Road();

	void	update() override;
};
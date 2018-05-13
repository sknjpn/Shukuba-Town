#pragma once

#include "Builder.h"
class Node;

class Builder_Road
	: public Builder
{
	class Sample
	{
		bool	m_is_selected;
		double	m_width;

	public:
		Sample(double width);

		double	get_width() const { return m_width; }

		void	set_selected(bool is_selected) { m_is_selected = is_selected; }

		bool	is_clicked(const s3d::Vec2& position) const;

		void	draw(const s3d::Vec2& position);
	};

	s3d::Vec2	m_from_position;
	s3d::Vec2	m_to_position;

	Sample*		m_selected_sample;
	std::vector<Sample*>	m_samples;

	void		set_from_position(const s3d::Vec2& position);
	void		set_to_position(const s3d::Vec2& position);

	double		get_path_width() const;
	double		get_node_radius() const;

	bool		can_set() const;

public:
	Builder_Road();

	void	update() override;
};
#pragma once

#include "Builder.h"
#include "Transform.h"

class Builder_Building
	: public Builder
{
	class Sample
	{
		bool		m_is_selected;
		Texture		m_texture;
		Polygon		m_base_shape;
		Polygon		m_base_site;
		Position	m_entrance;
		JSONValue	m_json;

	public:
		Sample(JSONValue json);

		//getter
		Texture			get_texture() const { return m_texture; }
		const Polygon&	get_base_shape() const { return m_base_shape; }
		const Polygon&	get_base_site() const { return m_base_site; }
		const Position&	get_entrance() const{ return m_entrance; }
		JSONValue		get_json() const { return m_json; }

		void	set_selected(bool is_selected) { m_is_selected = is_selected; }

		bool	is_clicked(const Vec2& position) const;

		bool	is_mouse_over(const Vec2& position) const;

		void	draw(const Vec2& position);
	};

	Vec2		m_grabbed_position;
	double		m_rotation;

	Sample*		m_selected_sample;
	std::vector<Sample*>	m_samples;

	bool		can_set() const;

	Position	get_setting_position() const;

public:
	Builder_Building();

	void		update() override;
};
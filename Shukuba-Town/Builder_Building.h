#pragma once

#include "Builder.h"

namespace skn
{
	class Builder_Building
		: public Builder
	{
		class Sample
		{
			bool				m_is_selected;
			s3d::Texture		m_texture;
			s3d::Polygon		m_base_shape;
			s3d::Polygon		m_base_site;
			s3d::JSONValue		m_json;

		public:
			Sample(s3d::JSONValue json);

			//getter
			s3d::Texture		get_texture() const { return m_texture; }
			const s3d::Polygon&	get_base_shape() const { return m_base_shape; }
			const s3d::Polygon&	get_base_site() const { return m_base_site; }
			s3d::JSONValue		get_json() const { return m_json; }

			void	set_selected(bool is_selected) { m_is_selected = is_selected; }

			bool	is_clicked(const s3d::Vec2& position) const;

			bool	is_mouse_over(const s3d::Vec2& position) const;

			void	draw(const s3d::Vec2& position);
		};

		s3d::Vec2	m_grabbed_position;
		double		m_rotation;

		Sample*		m_selected_sample;
		std::vector<Sample*>	m_samples;

		bool		can_set() const;

		s3d::Polygon		get_shape() const;
		s3d::Polygon		get_site() const;

	public:
		Builder_Building();

		void		update() override;
	};
}
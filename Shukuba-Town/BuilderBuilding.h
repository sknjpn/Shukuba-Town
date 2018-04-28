#pragma once

#include "Builder.h"

namespace skn
{
	class BuilderBuilding
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

			s3d::Texture		get_texture() const;
			const s3d::Polygon&	get_base_shape() const;
			const s3d::Polygon&	get_base_site() const;
			s3d::JSONValue		get_json() const;

			void	set_selected(bool is_selected);

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
		BuilderBuilding();

		void		update() override;
	};
}
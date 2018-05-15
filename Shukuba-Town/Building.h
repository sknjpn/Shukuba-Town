#pragma once

#include "Transform.h"
#include "Road.h"

namespace skn
{
	class Equipment;
	class Job;

	class Building
		: public Transform
		, public Uncopyable
	{
		//“üŒû‚ğ•\‚·
		class Entrance
			: public Anchor
		{
			Anchor*	m_anchor;

		public:
			Entrance(const Position& position)
				: Anchor(position)
			{}

			//getter
			const Anchor*	get_anchor() const { return m_anchor; }

			//‘S’Tõ‚µ‚ÄÅ“K‚ÈAnchor‚ÉÚ‘±‚·‚é
			void		update_connection();
		};

		Entrance		m_entrance;
		s3d::Polygon	m_base_site;
		s3d::Polygon	m_base_shape;
		s3d::Texture	m_texture;
		std::vector<Job*>		m_jobs;
		std::vector<Equipment*>	m_equipments;

		void	init_jobs(s3d::JSONValue json);
		void	init_equipments(s3d::JSONValue json);

	public:
		Building(const Position& position, const Rotation& rotation, s3d::JSONValue json);
		virtual ~Building() = default;

		s3d::Polygon	get_shape() const
		{
			return m_base_shape
				.rotated(get_rotation())
				.movedBy(get_position());
		}

		s3d::Polygon	get_site() const
		{
			return m_base_site
				.rotated(get_rotation())
				.movedBy(get_position());
		}

		void	draw() const;
	};
}
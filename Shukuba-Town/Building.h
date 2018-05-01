#pragma once

#include "Transform.h"
#include "Road.h"

namespace skn
{
	class Equipment;
	class Job;

	class Building
		: public Transform
	{
		//“üŒû‚ð•\‚·
		class Entrance
			: public Transform
		{
			Junction*	m_junction;

		public:
			Entrance(const Position& position)
				: Transform(position)
				, m_junction(nullptr)
			{}

			//getter
			const Junction*	get_junction() const { return m_junction; }
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
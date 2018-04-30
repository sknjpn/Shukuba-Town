#pragma once

#include "Transform.h"

namespace skn
{
	class Equipment;
	class Job;

	class Building
		: public Transform
	{
		class Entrance
		{
			Position		m_position;

		public:
			Entrance(const Position& position);

			const Position&	get_position() const;
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

		void	draw() const;

		s3d::Polygon	get_shape() const;
		s3d::Polygon	get_site() const;

		const std::vector<Equipment*>&	get_equipments() const;
	};
}
#pragma once

#include "Transform.h"

namespace skn
{
	class Equipment;

	class Building
		: public Transform
	{
		s3d::Vec2		m_entrance;
		s3d::Polygon	m_site;
		s3d::Polygon	m_shape;
		s3d::Texture	m_texture;
		std::vector<Equipment*>	m_equipments;

	public:
		Building(const Position& position, const Rotation& rotation, s3d::JSONValue json);
		virtual ~Building() = default;

		void	add_equipment(Equipment* equipment);

		void	draw() const;

		const s3d::Polygon&	get_shape() const;
		const s3d::Polygon&	get_site() const;

		const std::vector<Equipment*>&	get_equipments() const;
	};
}
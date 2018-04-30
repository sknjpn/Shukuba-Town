#pragma once

#include "Transform.h"

namespace skn
{
	class Equipment
		: public Transform
	{
		s3d::Polygon	m_base_shape;
		s3d::Texture	m_texture;	//テクスチャ

	public:
		Equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json);
		virtual ~Equipment() = default;

		s3d::Polygon	get_shape() const;

		void			draw() const;
	};
}
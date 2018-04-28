#pragma once

#include "Uncopyable.h"
#include "Transform.h"

namespace skn
{
	class Equipment
		: public Transform
	{
		s3d::Polygon	m_shape;
		s3d::Texture	m_texture;	//テクスチャ

	public:
		Equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json);
		virtual ~Equipment() = default;

		void			update();
	};
}
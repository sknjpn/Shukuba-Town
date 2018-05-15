#pragma once

#include "Transform.h"
#include "Drawable.h"

class Equipment
	: public Transform
	, public Uncopyable
	, public Drawable
{
	s3d::Polygon	m_base_shape;
	s3d::Texture	m_texture;	//テクスチャ

public:
	Equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json);
	virtual ~Equipment() = default;

	s3d::Polygon	get_shape() const
	{
		return m_base_shape
			.rotated(get_rotation())
			.movedBy(get_position());
	}

	void			draw() override;
};
#pragma once

#include "Transform.h"
#include "Drawable.h"

class Device
	: public Transform
	, public Uncopyable
{
	Polygon	m_base_shape;
	Texture	m_texture;	//テクスチャ

public:
	Device(const Position& position, const Rotation& rotation, JSONValue json);
	virtual ~Device() = default;

	const Texture& get_texture() const { return m_texture; }

	Polygon	get_shape() const
	{
		return m_base_shape
			.rotated(get_rotation())
			.movedBy(get_position());
	}
};
#pragma once

#include "Drawable.h"
#include "Transform.h"

class Building
	: public Drawable
	, public Transform
	, public Uncopyable
{
	Polygon m_shape;
	Polygon m_floor;
	Texture m_texture;

public:
	void draw() override {}

	const Polygon& get_shape() const { return m_shape; }
	const Polygon& get_floor() const { return m_floor; }
};
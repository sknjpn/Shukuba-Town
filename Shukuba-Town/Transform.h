#pragma once

using Position = Vec2;
using Rotation = double;

class Transform
{
	Position m_position;
	Rotation m_rotation;

public:
	Transform() : m_position(0, 0), m_rotation(0) {}
	Transform(const Position& position, const Rotation& rotation) : m_position(position), m_rotation(rotation) {}

	const Position& get_position() const { return m_position; }
	const Rotation& get_rotation() const { return m_rotation; }

	void set_position(const Position& position) { m_position = position; }
	void set_rotation(const Rotation& rotation) { m_rotation = rotation; }
};
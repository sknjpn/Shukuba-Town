#include "Transform.h"
#include "Equipment.h"

namespace skn
{
	Transform::Transform()
		: m_position()
		, m_rotation(0)
	{

	}

	Transform::Transform(const Position& position)
		: m_position(position)
		, m_rotation(0)
	{

	}

	Transform::Transform(const Position& position, const Rotation& rotation)
		: m_position(position)
		, m_rotation(rotation)
	{

	}

	const Position& Transform::get_position() const
	{
		return m_position;
	}

	const Rotation& Transform::get_rotation() const
	{
		return m_rotation;
	}

	void Transform::set_position(const Position& position)
	{
		m_position = position;
	}

	void Transform::set_rotation(const Rotation& rotation)
	{
		m_rotation = rotation;
	}
}
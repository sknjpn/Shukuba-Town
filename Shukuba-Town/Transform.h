#pragma once

namespace skn
{
	typedef s3d::Vec2	Position;
	typedef double		Rotation;

	class Transform
	{
		Position	m_position;
		Rotation	m_rotation;

	protected:
		~Transform() = default;

	public:
		Transform(const Position& position) : m_position(position), m_rotation(0) {}
		Transform(const Position& position, const Rotation& rotation) : m_position(position), m_rotation(rotation) {}

		const Position&	get_position() const { return m_position; }
		const Rotation&	get_rotation() const { return m_rotation; }

		void	set_position(const Position& position) { m_position = position; }
		void	set_rotation(const Rotation& rotation) { m_rotation = rotation; }
	};
}
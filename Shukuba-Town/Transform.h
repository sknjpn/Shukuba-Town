#pragma once

#include "Uncopyable.h"

namespace skn
{
	typedef s3d::Vec2	Position;
	typedef double		Rotation;

	class Transform
		: Uncopyable
	{
		Position	m_position;
		Rotation	m_rotation;
		std::vector<Transform*>	m_transforms;	//�d�Ȃ��Ă��鑼��Transform

	protected:
		~Transform();

	public:
		Transform(const Position& position);
		Transform(const Position& position, const Rotation& rotation);

		const Position&	get_position() const;
		const Rotation&	get_rotation() const;

		void	set_position(const Position& position);
		void	set_rotation(const Rotation& rotation);

		bool	intersects(const Transform& other) const;
	};
}
#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Camera
		: public Uncopyable	//コピー不可
	{
		s3d::RectF	m_target_region;
		s3d::RectF	m_smooth_region;
		double		m_following_speed;

	public:
		Camera();

		s3d::Transformer2D create_transformer() const;

		void	update();
	};
}
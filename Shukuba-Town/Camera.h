#pragma once

namespace skn
{
	class Camera
		: public Uncopyable	//コピー不可
	{
		RectF	m_target_region;
		RectF	m_smooth_region;
		double		m_following_speed;

	public:
		Camera();

		Transformer2D create_transformer() const;

		void	update();
	};
}
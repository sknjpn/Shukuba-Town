#include "Camera.h"

namespace skn
{
	Camera::Camera()
		: m_target_region(s3d::Window::ClientRect())
		, m_smooth_region(m_target_region)
		, m_following_speed(0.2)
	{

	}

	s3d::Transformer2D Camera::create_transformer() const
	{
		auto mat3x2 = s3d::Mat3x2::Translate(-m_smooth_region.center())
			.scaled(s3d::Window::Size().y / m_smooth_region.size.y)
			.translated(s3d::Window::ClientRect().center());

		return s3d::Transformer2D(mat3x2, true);
	}

	void    Camera::update()
	{
		//AspectRatioに基づく修正。WindowSizeが変わると対応できなくなるため。
		//m_target_region.w = m_target_region.h * s3d::Window::AspectRatio();
		//m_smooth_region.w = m_smooth_region.h * s3d::Window::AspectRatio();

		//ズームイン、アウト処理。createTransformer下で動かすと崩壊するので注意。
		{
			auto tc = create_transformer();
			const double delta = 0.1*s3d::Mouse::Wheel();    //ズームによる変動
			const auto position = m_target_region.pos + delta * (m_target_region.pos - s3d::Cursor::PosF());
			const auto size = (1.0 + delta)*m_target_region.size;
			m_target_region.set(position, size);
		}

		//描画領域の調節
		m_smooth_region.pos = m_smooth_region.pos*(1.0 - m_following_speed) + m_target_region.pos*m_following_speed;
		m_smooth_region.size = m_smooth_region.size*(1.0 - m_following_speed) + m_target_region.size*m_following_speed;

		//視点移動処理。フルスクリーンのゲームじゃないならキーボードによる操作にした方がいいかも
		if (s3d::KeyA.pressed() || s3d::Cursor::PosF().x <= 0) m_target_region.pos.x -= m_target_region.size.y*0.01;
		if (s3d::KeyW.pressed() || s3d::Cursor::PosF().y <= 0) m_target_region.pos.y -= m_target_region.size.y*0.01;
		if (s3d::KeyD.pressed() || s3d::Cursor::PosF().x >= s3d::Window::Size().x - 1) m_target_region.pos.x += m_target_region.size.y*0.01;
		if (s3d::KeyS.pressed() || s3d::Cursor::PosF().y >= s3d::Window::Size().y - 1) m_target_region.pos.y += m_target_region.size.y*0.01;
	}
}
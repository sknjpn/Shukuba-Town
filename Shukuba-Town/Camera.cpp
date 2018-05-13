#include "Camera.h"

Camera::Camera()
	: m_target_region(Window::ClientRect())
	, m_smooth_region(m_target_region)
	, m_following_speed(0.2)
{

}

Transformer2D Camera::create_transformer() const
{
	auto mat3x2 = Mat3x2::Translate(-m_smooth_region.center())
		.scaled(Window::Size().y / m_smooth_region.size.y)
		.translated(Window::ClientRect().center());

	return Transformer2D(mat3x2, true);
}

void    Camera::update()
{
	//AspectRatio�Ɋ�Â��C���BWindowSize���ς��ƑΉ��ł��Ȃ��Ȃ邽�߁B
	//m_target_region.w = m_target_region.h * Window::AspectRatio();
	//m_smooth_region.w = m_smooth_region.h * Window::AspectRatio();

	//�Y�[���C���A�A�E�g�����BcreateTransformer���œ������ƕ��󂷂�̂Œ��ӁB
	{
		auto tc = create_transformer();
		const double delta = 0.1*Mouse::Wheel();    //�Y�[���ɂ��ϓ�
		const auto position = m_target_region.pos + delta * (m_target_region.pos - Cursor::PosF());
		const auto size = (1.0 + delta)*m_target_region.size;
		m_target_region.set(position, size);
	}

	//�`��̈�̒���
	m_smooth_region.pos = m_smooth_region.pos*(1.0 - m_following_speed) + m_target_region.pos*m_following_speed;
	m_smooth_region.size = m_smooth_region.size*(1.0 - m_following_speed) + m_target_region.size*m_following_speed;

	//���_�ړ������B�t���X�N���[���̃Q�[������Ȃ��Ȃ�L�[�{�[�h�ɂ�鑀��ɂ���������������
	if (KeyA.pressed() || Cursor::PosF().x <= 0) m_target_region.pos.x -= m_target_region.size.y*0.01;
	if (KeyW.pressed() || Cursor::PosF().y <= 0) m_target_region.pos.y -= m_target_region.size.y*0.01;
	if (KeyD.pressed() || Cursor::PosF().x >= Window::Size().x - 1) m_target_region.pos.x += m_target_region.size.y*0.01;
	if (KeyS.pressed() || Cursor::PosF().y >= Window::Size().y - 1) m_target_region.pos.y += m_target_region.size.y*0.01;
}

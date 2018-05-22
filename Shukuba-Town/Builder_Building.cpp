#include "Builder_Building.h"

#include "Building.h"
#include "Field.h"

#include "Factory.h"
#include "Camera.h"

#include "Road.h"
#include "Node.h"

#include "Menu.h"

bool Builder_Building::can_set() const
{
	auto shape =
		m_model.m_base_shape
		.rotated(m_rotation)
		.movedBy(get_setting_position());

	//ほかのBuildingとの重なり
	for (auto* b : g_field->get_buildings())
	{
		if (b->get_shape().intersects(shape))
		{
			return false;
		}
	}

	//Roadとの重なり
	for (auto* r : g_field->get_roads())
	{
		if (r->get_line().intersects(shape))
		{
			return false;
		}
	}

	return true;
}

Position Builder_Building::get_setting_position() const
{
	auto entrance = Cursor::PosF() + m_model.m_entrance_position.rotated(m_rotation);
	auto* node = g_field->get_closest_node(entrance);

	if (node == nullptr || node->get_position().distanceFrom(entrance) > Node::s_radius)
	{
		return Cursor::PosF();
	}
	else
	{
		return node->get_position() - m_model.m_entrance_position.rotated(m_rotation);
	}
}

Builder_Building::Builder_Building(JSONValue json)
	: m_rotation(0)
	, m_model(json)
{

}

void Builder_Building::update()
{
	Print << U"建物建設モード";

	if (g_field->get_menu()->any_mouse_over()) { return; }

	if (Cursor::PosF().y < Window::Size().y - 80)
	{
		//Transformer2D
		auto t = g_field->get_camera()->create_transformer();

		if (MouseR.down())
		{
			m_grabbed_position = Cursor::PosF();// .movedBy(Vec2::Left(48.0).rotated(m_rotation));
		}

		if (MouseR.pressed())
		{
			auto vector = Cursor::PosF() - m_grabbed_position;

			m_rotation = atan2(vector.y, vector.x);
		}

		if (MouseL.down() && can_set())
		{
			auto position = Cursor::PosF();
			auto* node = g_field->get_node(position);

			if (node == nullptr) { node = new Node(position); }

			new Building(node, m_rotation, m_model.m_json);
		}

		{
			auto color = can_set() ? Palette::Green : Palette::Red;
			auto position = get_setting_position();

			m_model.m_texture
				.rotated(m_rotation)
				.drawAt(get_setting_position(), ColorF(color, 0.50));

			m_model.m_base_shape
				.rotated(m_rotation)
				.movedBy(position).drawFrame(1, ColorF(color, 0.50));

			m_model.m_base_site
				.rotated(m_rotation)
				.movedBy(position).drawFrame(1, ColorF(color, 0.25));
		}

		if (MouseR.pressed())
		{
			Circle(m_grabbed_position, 12.0)
				.drawFrame(4.0);

			Line(m_grabbed_position, Cursor::PosF())
				.drawArrow(4.0, Vec2(16.0, 16.0));
		}
	}
}

Model::Model(JSONValue json)
	: m_json(json)
	, m_entrance_position(json[U"entrance"].get<Vec2>())
{
	s3d::Image	image_shape(json[U"texture"][U"shape"].get<s3d::FilePath>());
	s3d::Image	image_site(json[U"texture"][U"site"].get<s3d::FilePath>());

	m_texture = s3d::Texture(image_shape);

	m_base_shape = s3d::ImageProcessing::FindExternalContour(image_shape, true)
		.movedBy(s3d::Vec2::One() / 2.0)
		.movedBy(-image_shape.size() / 2.0)
		.calculateRoundBuffer(16.0);

	m_base_site = s3d::ImageProcessing::FindExternalContour(image_site, true)
		.movedBy(s3d::Vec2::One() / 2.0)
		.movedBy(-image_site.size() / 2.0);
}
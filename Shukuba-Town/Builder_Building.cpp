#include "Builder_Building.h"

#include "Sample_Building.h"

#include "Building.h"
#include "Field.h"

#include "Factory.h"
#include "Camera.h"

#include "Path.h"
#include "Node.h"

bool Builder_Building::can_set() const
{
	auto* sample = dynamic_cast<Sample_Building*>(get_selected_sample());

	if (sample == nullptr) { return false; }

	auto shape =
		sample->get_base_shape()
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
	for (auto* p : g_field->get_paths())
	{
		if (p->get_line().intersects(shape))
		{
			return false;
		}
	}

	return true;
}

Position Builder_Building::get_setting_position() const
{
	auto entrance = Cursor::PosF() + dynamic_cast<Sample_Building*>(get_selected_sample())->get_entrance().rotated(m_rotation);
	auto* node = g_field->get_closest_node(entrance);

	if (node == nullptr || node->get_position().distanceFrom(entrance) > Node::s_radius)
	{
		return Cursor::PosF();
	}
	else
	{
		return node->get_position() - dynamic_cast<Sample_Building*>(get_selected_sample())->get_entrance().rotated(m_rotation);
	}
}

Builder_Building::Builder_Building()
	: m_rotation(0)
{
	RectF rect(Vec2(20, Window::Size().y - 100), 80, 80);

	for (auto json : g_field->get_json()[U"buildings"].arrayView())
	{
		add_sample(new Sample_Building(rect, json));

		rect.moveBy(100, 0);
	}
}

void Builder_Building::update()
{
	Print << U"建物建設モード";

	auto* sample = dynamic_cast<Sample_Building*>(get_selected_sample());

	if (sample == nullptr) { return; }

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
			auto json = sample->get_json();
			auto position = Cursor::PosF();
			auto* node = g_field->get_node(position);

			if (node == nullptr) { node = new Node(position); }

			new Building(node, m_rotation, json);
		}

		{
			auto color = can_set() ? Palette::Green : Palette::Red;
			auto position = get_setting_position();

			sample->get_texture()
				.rotated(m_rotation)
				.drawAt(get_setting_position(), ColorF(color, 0.50));

			sample->get_base_shape()
				.rotated(m_rotation)
				.movedBy(position).drawFrame(1, ColorF(color, 0.50));

			sample->get_base_site()
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
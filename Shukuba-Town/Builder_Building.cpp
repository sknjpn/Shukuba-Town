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
	auto shape =
		get_selected_sample()->get_base_shape()
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
	auto entrance = Cursor::PosF() + get_selected_sample()->get_entrance().rotated(m_rotation);
	auto* node = g_field->get_closest_node(entrance);

	if (node == nullptr || node->get_position().distanceFrom(entrance) > Node::s_radius)
	{
		return Cursor::PosF();
	}
	else
	{
		return node->get_position() - get_selected_sample()->get_entrance().rotated(m_rotation);
	}
}

Builder_Building::Builder_Building()
	: m_rotation(0)
{
	for (auto json : g_field->get_json()[U"buildings"].arrayView())
	{
		m_samples.emplace_back(new Sample(json));
	}

	get_selected_sample() = m_samples.front();
	get_selected_sample()->set_selected(true);
}

void Builder_Building::update()
{
	Print << U"建物建設モード";

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
			auto json = get_selected_sample()->get_json();
			auto position = Cursor::PosF();
			auto* node = g_field->get_node(position);

			if (node == nullptr) { node = new Node(position); }

			new Building(node, m_rotation, json);
		}

		{
			auto color = can_set() ? Palette::Green : Palette::Red;
			auto position = get_setting_position();

			get_selected_sample()->get_texture()
				.rotated(m_rotation)
				.drawAt(get_setting_position(), ColorF(color, 0.50));

			get_selected_sample()->get_base_shape()
				.rotated(m_rotation)
				.movedBy(position).drawFrame(1, ColorF(color, 0.50));

			get_selected_sample()->get_base_site()
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

	for (int i = 0; i < int(m_samples.size()); ++i)
	{
		auto* s = m_samples[i];
		auto position = Vec2(8 + i * 80, Window::Size().y - 72);

		if (s->is_clicked(position))
		{
			get_selected_sample()->set_selected(false);
			get_selected_sample() = s;
			get_selected_sample()->set_selected(true);
		}

		s->draw(position);
	}
}

Builder_Building::Sample::Sample(JSONValue json)
	: m_is_selected(false)
	, m_json(json)
	, m_entrance(json[U"entrance"].get<Position>())
{
	Image	image_shape(json[U"texture"][U"shape"].get<FilePath>());
	Image	image_site(json[U"texture"][U"site"].get<FilePath>());

	m_texture = Texture(image_shape);

	m_base_shape = ImageProcessing::FindExternalContour(image_shape, true)
		.movedBy(Vec2::One() / 2.0)
		.movedBy(-image_shape.size() / 2.0)
		.calculateRoundBuffer(16.0);

	m_base_site = ImageProcessing::FindExternalContour(image_site, true)
		.movedBy(Vec2::One() / 2.0)
		.movedBy(-image_site.size() / 2.0);
}

bool Builder_Building::Sample::is_clicked(const Vec2& position) const
{
	return RoundRect(Rect(64), 8)
		.movedBy(position)
		.leftClicked();
}

bool Builder_Building::Sample::is_mouse_over(const Vec2& position) const
{
	auto rect = Rect(64);

	return RoundRect(rect, 8)
		.movedBy(position)
		.mouseOver();
}

void Builder_Building::Sample::draw(const Vec2& position)
{
	auto color = m_is_selected ? Palette::Orange : Palette::White;
	auto rect = Rect(64);

	RoundRect(rect, 8)
		.movedBy(position)
		.draw(ColorF(color, 0.5))
		.drawFrame(1.0, color);

	m_texture
		.resized(rect.size)
		.draw(position);
}
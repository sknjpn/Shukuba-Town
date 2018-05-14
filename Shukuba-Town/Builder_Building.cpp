#include "BuilderBuilding.h"

#include "Building.h"
#include "Village.h"

#include "Factory.h"

#include "Road.h"

namespace skn
{
	bool BuilderBuilding::can_set() const
	{
		auto shape = get_shape();

		//ほかのBuildingとの重なり
		for (auto* b : g_village->get_buildings())
		{
			if (b->get_shape().intersects(shape))
			{
				return false;
			}
		}

		//Roadとの重なり
		for (auto* p : g_village->get_roads())
		{
			if (p->get_line().intersects(shape))
			{
				return false;
			}
		}

		return true;
	}

	Polygon BuilderBuilding::get_shape() const
	{
		return m_selected_sample->get_base_shape()
			.rotated(m_rotation)
			.movedBy(Cursor::PosF());
	}

	Polygon BuilderBuilding::get_site() const
	{
		return m_selected_sample->get_base_site()
			.rotated(m_rotation)
			.movedBy(Cursor::PosF());
	}

	BuilderBuilding::BuilderBuilding()
		: m_rotation(0)
	{
		for (auto json : g_village->get_json()[U"buildings"].arrayView())
		{
			m_samples.emplace_back(new Sample(json));
		}

		m_selected_sample = m_samples.front();
		m_selected_sample->set_selected(true);
	}

	void BuilderBuilding::update()
	{
		Print << U"建物建設モード";

		if (Cursor::PosF().y < Window::Size().y - 80)
		{
			//Transformer2D
			auto t = g_village->get_camera().create_transformer();

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
				auto json = m_selected_sample->get_json();

				g_village->add_building(Factory::make_building(Cursor::PosF(), m_rotation, json));
			}

			{
				auto color = can_set() ? Palette::Green : Palette::Red;

				m_selected_sample->get_texture()
					.rotated(m_rotation)
					.drawAt(Cursor::PosF(), ColorF(color, 0.50));

				get_shape().drawFrame(1, ColorF(color, 0.50));

				get_site().drawFrame(1, ColorF(color, 0.25));
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
				m_selected_sample->set_selected(false);
				m_selected_sample = s;
				m_selected_sample->set_selected(true);
			}

			s->draw(position);
		}
	}

	BuilderBuilding::Sample::Sample(JSONValue json)
		: m_is_selected(false)
		, m_json(json)
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

	bool BuilderBuilding::Sample::is_clicked(const Vec2& position) const
	{
		return RoundRect(Rect(64), 8)
			.movedBy(position)
			.leftClicked();
	}

	bool BuilderBuilding::Sample::is_mouse_over(const Vec2& position) const
	{
		auto rect = Rect(64);

		return RoundRect(rect, 8)
			.movedBy(position)
			.mouseOver();
	}

	void BuilderBuilding::Sample::draw(const Vec2& position)
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
}
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

		//Pathとの重なり
		for (auto* p : g_village->get_paths())
		{
			if (p->get_line().intersects(shape))
			{
				return false;
			}
		}

		return true;
	}

	s3d::Polygon BuilderBuilding::get_shape() const
	{
		return m_selected_sample->get_base_shape()
			.rotated(m_rotation)
			.movedBy(s3d::Cursor::PosF());
	}

	s3d::Polygon BuilderBuilding::get_site() const
	{
		return m_selected_sample->get_base_site()
			.rotated(m_rotation)
			.movedBy(s3d::Cursor::PosF());
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
		s3d::Print << U"建物建設モード";

		if (s3d::Cursor::PosF().y < s3d::Window::Size().y - 80)
		{
			//Transformer2D
			auto t = g_village->get_camera().create_transformer();

			if (s3d::MouseR.down())
			{
				m_grabbed_position = s3d::Cursor::PosF();// .movedBy(s3d::Vec2::Left(48.0).rotated(m_rotation));
			}

			if (s3d::MouseR.pressed())
			{
				auto vector = s3d::Cursor::PosF() - m_grabbed_position;

				m_rotation = atan2(vector.y, vector.x);
			}

			if (s3d::MouseL.down() && can_set())
			{
				auto json = m_selected_sample->get_json();

				g_village->add_building(Factory::make_building(s3d::Cursor::PosF(), m_rotation, json));
			}

			{
				auto color = can_set() ? s3d::Palette::Green : s3d::Palette::Red;

				m_selected_sample->get_texture()
					.rotated(m_rotation)
					.drawAt(s3d::Cursor::PosF(), s3d::ColorF(color, 0.50));

				get_shape().drawFrame(1, s3d::ColorF(color, 0.50));

				get_site().drawFrame(1, s3d::ColorF(color, 0.25));
			}

			if (s3d::MouseR.pressed())
			{
				s3d::Circle(m_grabbed_position, 12.0)
					.drawFrame(4.0);

				s3d::Line(m_grabbed_position, s3d::Cursor::PosF())
					.drawArrow(4.0, s3d::Vec2(16.0, 16.0));
			}
		}

		for (int i = 0; i < int(m_samples.size()); ++i)
		{
			auto* s = m_samples[i];
			auto position = s3d::Vec2(8 + i * 80, s3d::Window::Size().y - 72);

			if (s->is_clicked(position))
			{
				m_selected_sample->set_selected(false);
				m_selected_sample = s;
				m_selected_sample->set_selected(true);
			}

			s->draw(position);
		}
	}

	BuilderBuilding::Sample::Sample(s3d::JSONValue json)
		: m_is_selected(false)
		, m_json(json)
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

	bool BuilderBuilding::Sample::is_clicked(const s3d::Vec2& position) const
	{
		return s3d::RoundRect(s3d::Rect(64), 8)
			.movedBy(position)
			.leftClicked();
	}

	bool BuilderBuilding::Sample::is_mouse_over(const s3d::Vec2& position) const
	{
		auto rect = s3d::Rect(64);

		return s3d::RoundRect(rect, 8)
			.movedBy(position)
			.mouseOver();
	}

	void BuilderBuilding::Sample::draw(const s3d::Vec2& position)
	{
		auto color = m_is_selected ? s3d::Palette::Orange : s3d::Palette::White;
		auto rect = s3d::Rect(64);

		s3d::RoundRect(rect, 8)
			.movedBy(position)
			.draw(s3d::ColorF(color, 0.5))
			.drawFrame(1.0, color);

		m_texture
			.resized(rect.size)
			.draw(position);
	}
}
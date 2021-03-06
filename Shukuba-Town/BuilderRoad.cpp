#include "BuilderRoad.h"

#include "Village.h"

#include "Road.h"
#include "Building.h"

namespace skn
{
	void BuilderRoad::set_from_position(const s3d::Vec2 & position)
	{
		auto* c_road = g_village->get_closest_road(position);

		if (c_road != nullptr && c_road->get_distance_from(position) <= get_node_radius() * 2.0)
		{
			m_from_position = c_road->get_closest(position);

			auto* c_node = g_village->get_closest_node(position);

			if (c_node != nullptr && c_node->get_position().distanceFrom(position) <= get_node_radius() * 2.0)
			{
				m_from_position = c_node->get_position();

				return;	//Node上にある場合
			}
			else
			{
				return;	//線上にある場合
			}
		}

		//それ以外
		m_from_position = position;
	}

	void BuilderRoad::set_to_position(const s3d::Vec2 & position)
	{
		auto* c_road = g_village->get_closest_road(position);

		if (c_road != nullptr && c_road->get_distance_from(position) <= get_node_radius() * 2.0)
		{
			m_to_position = c_road->get_closest(position);

			auto* c_node = g_village->get_closest_node(position);

			if (c_node != nullptr && c_node->get_position().distanceFrom(position) <= get_node_radius() * 2.0)
			{
				m_to_position = c_node->get_position();

				return;	//Node上にある場合
			}
			else
			{
				return;	//線上にある場合
			}
		}

		//それ以外
		m_to_position = position;
	}

	double BuilderRoad::get_road_width() const
	{
		return m_selected_sample->get_width();
	}

	bool BuilderRoad::can_set() const
	{
		const s3d::Line line(m_from_position, m_to_position);

		//Node間距離に対する制限
		if (m_from_position.distanceFrom(m_to_position) <= get_node_radius() * 2.0)
		{
			s3d::Print << U"f1";

			return false;
		}

		//RoadとNode間距離に対する制限
		for (auto* n : g_village->get_nodes())
		{
			if (line.closest(n->get_position()).distanceFrom(n->get_position()) <= get_node_radius() * 2.0 &&
				line.begin != n->get_position() &&
				line.end != n->get_position())
			{
				s3d::Print << U"f2";

				return false;
			}
		}

		//Road交差に対する制限
		for (auto* p : g_village->get_roads())
		{
			auto position = line.intersectsAt(p->get_line());
			auto length = 1.0;

			if (position &&
				(position.value() - m_from_position).length() > length &&
				(position.value() - m_to_position).length() > length &&
				(position.value() - p->get_from()->get_position()).length() > length &&
				(position.value() - p->get_to()->get_position()).length() > length)
			{
				s3d::Print << U"f3";

				return false;
			}
		}

		{
			auto* from_node = g_village->get_node(m_from_position);
			auto* to_node = g_village->get_node(m_to_position);

			//すでにある接続に対する制限
			if (from_node != nullptr && to_node != nullptr && from_node->get_road(to_node) != nullptr)
			{
				s3d::Print << U"f4";

				return false;
			}

			//すでにあるパスに対する接続への制限
			for (auto* p : g_village->get_roads())
			{
				if (p->get_line().intersects(m_from_position) &&
					!p->has(from_node) &&
					p->get_line().intersects(m_to_position) &&
					!p->has(to_node))
				{
					s3d::Print << U"f5";

					return false;
				}
			}
		}

		//Buildingとの衝突に関する制限
		for (auto* b : g_village->get_buildings())
		{
			if (b->get_shape().intersects(line))
			{
				s3d::Print << U"f6";

				return false;
			}
		}

		return true;
	}

	double BuilderRoad::get_node_radius() const
	{
		return 16.0;
	}

	BuilderRoad::BuilderRoad()
	{
		m_samples.emplace_back(new Sample(16.0));
		m_samples.emplace_back(new Sample(24.0));
		m_samples.emplace_back(new Sample(32.0));
		m_selected_sample = m_samples.front();
		m_selected_sample->set_selected(true);
	}

	void BuilderRoad::update()
	{
		s3d::Print << U"道路建設モード";

		//if (s3d::Cursor::PosF().y < s3d::Window::Size().y - 80)
		{
			//Transformer2D
			auto t = g_village->get_camera().create_transformer();

			set_to_position(s3d::Cursor::PosF());

			if (s3d::MouseL.pressed() && can_set())
			{
				auto* from_node = g_village->get_node(m_from_position);
				auto* to_node = g_village->get_node(m_to_position);

				if (from_node == nullptr) { from_node = g_village->add_node(new Node(m_from_position, get_node_radius())); }
				if (to_node == nullptr) { to_node = g_village->add_node(new Node(m_to_position, get_node_radius())); }

				{
					auto roads = g_village->get_roads();

					for (auto* p : roads)
					{
						if (p->get_line().intersects(m_from_position) && !p->has(from_node))
						{
							p->get_from()->connect(from_node, p->get_width());
							p->get_to()->connect(from_node, p->get_width());

							p->disconnect();
						}
						else if (p->get_line().intersects(m_to_position) && !p->has(to_node))
						{
							p->get_from()->connect(to_node, p->get_width());
							p->get_to()->connect(to_node, p->get_width());

							p->disconnect();
						}
					}
				}

				//接続
				from_node->connect(to_node, get_road_width());

				//fromの転換
				set_from_position(m_to_position);
			}

			if (!s3d::MouseL.pressed())
			{
				set_from_position(m_to_position);
			}

			//描画
			{
				auto color = s3d::ColorF(can_set() ? s3d::Palette::Green : s3d::Palette::Red, 0.5);

				if (m_from_position.distanceFrom(m_to_position) > 1.0)
				{
					auto p1 = m_from_position;
					auto p2 = m_to_position;
					auto vector = (p1 - p2).setLength(get_road_width() / 2.0).rotated(s3d::Math::HalfPi);

					s3d::Array<s3d::Vec2> points{ p1 - vector, p1 + vector, p2 + vector, p2 - vector, };
					s3d::Polygon shape(points);
					shape.append(s3d::Circle(p1, get_road_width() / 2.0).asPolygon());
					shape.append(s3d::Circle(p2, get_road_width() / 2.0).asPolygon());

					shape.draw(color);
				}
				else
				{
					s3d::Circle(m_from_position, get_road_width() / 2.0).draw(color);
				}
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

	BuilderRoad::Sample::Sample(double width)
		: m_is_selected(false)
		, m_width(width)
	{

	}

	bool BuilderRoad::Sample::is_clicked(const s3d::Vec2& position) const
	{
		return s3d::RoundRect(s3d::Rect(64), 8)
			.movedBy(position)
			.leftClicked();
	}

	void BuilderRoad::Sample::draw(const s3d::Vec2& position)
	{
		auto color = m_is_selected ? s3d::Palette::Orange : s3d::Palette::White;

		s3d::RoundRect(s3d::Rect(64), 8)
			.movedBy(position)
			.draw(s3d::ColorF(color, 0.5))
			.drawFrame(1.0, color);

		s3d::Circle(position.movedBy(32, 32), m_width / 2.0).draw(s3d::Palette::Darkgreen);
		s3d::Circle(position.movedBy(32, 32), m_width / 4.0).draw(s3d::Palette::Khaki);
	}
}
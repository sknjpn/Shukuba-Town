#include "BuilderRoad.h"

#include "Village.h"

#include "Node.h"
#include "Path.h"
#include "Building.h"

namespace skn
{
	void BuilderRoad::set_from_position(const s3d::Vec2 & position)
	{
		auto* c_path = g_village->get_closest_path(position);

		if (c_path != nullptr && c_path->get_distance_from(position) <= get_node_radius() * 2.0)
		{
			m_from_position = c_path->get_closest(position);

			auto* c_node = g_village->get_closest_node(position);

			if (c_node != nullptr && c_node->get_distance_from(position) <= get_node_radius() * 2.0)
			{
				m_from_position = c_node->get_position();

				return;	//Nodeè„Ç…Ç†ÇÈèÍçá
			}
			else
			{
				return;	//ê¸è„Ç…Ç†ÇÈèÍçá
			}
		}

		//ÇªÇÍà»äO
		m_from_position = position;
	}

	void BuilderRoad::set_to_position(const s3d::Vec2 & position)
	{
		auto* c_path = g_village->get_closest_path(position);

		if (c_path != nullptr && c_path->get_distance_from(position) <= get_node_radius() * 2.0)
		{
			m_to_position = c_path->get_closest(position);

			auto* c_node = g_village->get_closest_node(position);

			if (c_node != nullptr && c_node->get_distance_from(position) <= get_node_radius() * 2.0)
			{
				m_to_position = c_node->get_position();

				return;	//Nodeè„Ç…Ç†ÇÈèÍçá
			}
			else
			{
				return;	//ê¸è„Ç…Ç†ÇÈèÍçá
			}
		}

		//ÇªÇÍà»äO
		m_to_position = position;
	}

	double BuilderRoad::get_path_width() const
	{
		return m_selected_sample->get_width();
	}

	bool BuilderRoad::can_set() const
	{
		const s3d::Line line(m_from_position, m_to_position);

		//Nodeä‘ãóó£Ç…ëŒÇ∑ÇÈêßå¿
		if (m_from_position.distanceFrom(m_to_position) <= get_node_radius() * 2.0)
		{
			s3d::Print << U"f1";

			return false;
		}

		//PathÇ∆Nodeä‘ãóó£Ç…ëŒÇ∑ÇÈêßå¿
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

		//Pathåç∑Ç…ëŒÇ∑ÇÈêßå¿
		for (auto* p : g_village->get_paths())
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

			//Ç∑Ç≈Ç…Ç†ÇÈê⁄ë±Ç…ëŒÇ∑ÇÈêßå¿
			if (from_node != nullptr && to_node != nullptr && from_node->get_path(to_node) != nullptr)
			{
				s3d::Print << U"f4";

				return false;
			}

			//Ç∑Ç≈Ç…Ç†ÇÈÉpÉXÇ…ëŒÇ∑ÇÈê⁄ë±Ç÷ÇÃêßå¿
			for (auto* p : g_village->get_paths())
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

		//BuildingÇ∆ÇÃè’ìÀÇ…ä÷Ç∑ÇÈêßå¿
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
		s3d::Print << U"ìπòHåöê›ÉÇÅ[Éh";

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
					auto paths = g_village->get_paths();

					for (auto* p : paths)
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

				//ê⁄ë±
				from_node->connect(to_node, get_path_width());

				//fromÇÃì]ä∑
				set_from_position(m_to_position);
			}

			if (!s3d::MouseL.pressed())
			{
				set_from_position(m_to_position);
			}

			//ï`âÊ
			{
				auto color = s3d::ColorF(can_set() ? s3d::Palette::Green : s3d::Palette::Red, 0.5);

				if (m_from_position.distanceFrom(m_to_position) > 1.0)
				{
					auto p1 = m_from_position;
					auto p2 = m_to_position;
					auto vector = (p1 - p2).setLength(get_path_width() / 2.0).rotated(s3d::Math::HalfPi);

					s3d::Array<s3d::Vec2> points{ p1 - vector, p1 + vector, p2 + vector, p2 - vector, };
					s3d::Polygon shape(points);
					shape.append(s3d::Circle(p1, get_path_width() / 2.0).asPolygon());
					shape.append(s3d::Circle(p2, get_path_width() / 2.0).asPolygon());

					shape.draw(color);
				}
				else
				{
					s3d::Circle(m_from_position, get_path_width() / 2.0).draw(color);
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

	double BuilderRoad::Sample::get_width() const
	{
		return m_width;
	}

	void BuilderRoad::Sample::set_selected(bool is_selected)
	{
		m_is_selected = is_selected;
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
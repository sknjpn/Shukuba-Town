#include "Builder_Road.h"

#include "Sample_Road.h"

#include "Field.h"
#include "Camera.h"

#include "Node.h"
#include "Path.h"
#include "Building.h"

void Builder_Road::set_from_position(const Vec2& position)
{
	auto* c_path = g_field->get_closest_path(position);

	if (c_path != nullptr && Geometry2D::Distance(c_path->get_line(), position) <= Node::s_radius * 2.0)
	{
		m_from_position = c_path->get_line().closest(position);

		auto* c_node = g_field->get_closest_node(position);

		if (c_node != nullptr && c_node->get_position().distanceFrom(position) <= Node::s_radius * 2.0)
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

void Builder_Road::set_to_position(const Vec2& position)
{
	auto* c_path = g_field->get_closest_path(position);

	if (c_path != nullptr && Geometry2D::Distance(c_path->get_line(), position) <= Node::s_radius * 2.0)
	{
		m_to_position = c_path->get_line().closest(position);

		auto* c_node = g_field->get_closest_node(position);

		if (c_node != nullptr && c_node->get_position().distanceFrom(position) <= Node::s_radius * 2.0)
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

bool Builder_Road::can_set() const
{
	const Line line(m_from_position, m_to_position);

	//Node間距離に対する制限
	if (m_from_position.distanceFrom(m_to_position) <= Node::s_radius * 2.0)
	{
		Print << U"f1";

		return false;
	}

	//pathとNode間距離に対する制限
	for (auto* n : g_field->get_nodes())
	{
		if (line.closest(n->get_position()).distanceFrom(n->get_position()) <= Node::s_radius * 2.0 &&
			line.begin != n->get_position() &&
			line.end != n->get_position())
		{
			Print << U"f2";

			return false;
		}
	}

	//path交差に対する制限
	for (auto* p : g_field->get_paths())
	{
		auto position = line.intersectsAt(p->get_line());
		auto length = 1.0;

		if (position &&
			(position.value() - m_from_position).length() > length &&
			(position.value() - m_to_position).length() > length &&
			(position.value() - p->get_from()->get_position()).length() > length &&
			(position.value() - p->get_to()->get_position()).length() > length)
		{
			Print << U"f3";

			return false;
		}
	}

	{
		auto* from_node = g_field->get_node(m_from_position);
		auto* to_node = g_field->get_node(m_to_position);

		//すでにある接続に対する制限
		if (from_node != nullptr && to_node != nullptr && from_node->get_path(to_node) != nullptr)
		{
			Print << U"f4";

			return false;
		}

		//すでにあるパスに対する接続への制限
		for (auto* p : g_field->get_paths())
		{
			if (p->get_line().intersects(m_from_position) &&
				p->get_line().intersects(m_to_position) &&
				p->get_from() != from_node &&
				p->get_from() != to_node &&
				p->get_to() != from_node &&
				p->get_to() != to_node)
			{
				Print << U"f5";

				return false;
			}
		}
	}

	//Buildingとの衝突に関する制限
	for (auto* b : g_field->get_buildings())
	{
		if (b->get_shape().intersects(line))
		{
			Print << U"f6";

			return false;
		}
	}

	return true;
}

Builder_Road::Builder_Road()
{
	m_samples.emplace_back(new Sample(16.0));
	m_samples.emplace_back(new Sample(24.0));
	m_samples.emplace_back(new Sample(32.0));
	m_selected_sample = m_samples.front();
	m_selected_sample->set_selected(true);
}

void Builder_Road::update()
{
	Print << U"道路建設モード";

	//if (Cursor::PosF().y < Window::Size().y - 80)
	{
		//Transformer2D
		auto t = g_field->get_camera()->create_transformer();

		set_to_position(Cursor::PosF());

		if (MouseL.pressed() && can_set())
		{
			auto* from_node = g_field->get_node(m_from_position);
			auto* to_node = g_field->get_node(m_to_position);

			if (from_node == nullptr) { from_node = new Node(m_from_position); }
			if (to_node == nullptr) { to_node = new Node(m_to_position); }

			{
				auto paths = g_field->get_paths();

				for (auto* p : paths)
				{
					if (p->get_line().intersects(m_from_position) &&
						p->get_from() != from_node &&
						p->get_to() != from_node)
					{
						p->get_from()->connect(from_node);
						p->get_to()->connect(from_node);

						p->get_from()->disconnect(p->get_to());
						p->get_to()->disconnect(p->get_from());
					}
					else if (p->get_line().intersects(m_to_position) &&
						p->get_from() != to_node &&
						p->get_to() != to_node)
					{
						p->get_from()->connect(to_node);
						p->get_to()->connect(to_node);

						p->get_from()->disconnect(p->get_to());
						p->get_to()->disconnect(p->get_from());
					}
				}
			}

			//接続
			from_node->connect(to_node);

			//fromの転換
			set_from_position(m_to_position);
		}

		if (!MouseL.pressed())
		{
			set_from_position(m_to_position);
		}

		//描画
		{
			auto color = ColorF(can_set() ? Palette::Green : Palette::Red, 0.5);

			if (m_from_position.distanceFrom(m_to_position) > 1.0)
			{
				auto p1 = m_from_position;
				auto p2 = m_to_position;
				auto vector = (p1 - p2).setLength(Node::s_radius).rotated(Math::HalfPi);

				Array<Vec2> points{ p1 - vector, p1 + vector, p2 + vector, p2 - vector, };
				Polygon shape(points);
				shape.append(Circle(p1, Node::s_radius).asPolygon());
				shape.append(Circle(p2, Node::s_radius).asPolygon());

				shape.draw(color);
			}
			else
			{
				Circle(m_from_position, Node::s_radius).draw(color);
			}
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

void Builder_Road::Sample::draw(const Vec2& position)
{
}

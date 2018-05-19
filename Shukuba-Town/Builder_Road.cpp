#include "Builder_Road.h"

#include "Sample_Road.h"

#include "Field.h"
#include "Camera.h"

#include "Road.h"
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

			for (auto* r : g_field->get_roads())
			{
				if (r->get_line().intersects(m_from_position) &&
					r->get_from() != from_node &&
					r->get_to() != from_node)
				{
					new Road(r->get_from(), from_node);
					new Road(r->get_to(), from_node);

					delete r;
				}
				else if (r->get_line().intersects(m_to_position) &&
					r->get_from() != to_node &&
					r->get_to() != to_node)
				{
					new Road(r->get_from(), to_node);
					new Road(r->get_to(), to_node);

					delete r;
				}
			}

			//接続
			new Road(from_node, to_node);

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
}

#include "Field.h"
#include "Builder.h"
#include "Camera.h"
#include "Menu.h"
#include "Node.h"
#include "Path.h"
#include "Road.h"
#include "Building.h"
#include "Device.h"

#include "Builder_Road.h"
#include "Builder_Building.h"

Field* g_field = nullptr;

Field::Field()
	: m_json(U"data/data.json")
{
	m_builder = nullptr;
	m_camera = new Camera();
	m_menu = new Menu(m_json);
}


Field::~Field()
{
	delete m_camera;
	delete m_menu;
}

void Field::set_builder(Builder* builder)
{
	if (m_builder != nullptr) { delete m_builder; }

	m_builder = builder;
}

Road* Field::get_closest_road(const Vec2 & position) const
{
	auto it = std::min_element(
		m_roads.begin(),
		m_roads.end(),
		[&position](Road* a, Road* b) { return Geometry2D::Distance(a->get_line(), position) < Geometry2D::Distance(b->get_line(), position); }
	);

	return (it == m_roads.end()) ? nullptr : *it;
}

Node* Field::get_closest_node(const Vec2 & position) const
{
	auto it = std::min_element(
		m_nodes.begin(),
		m_nodes.end(),
		[&position](Node* a, Node* b) { return a->get_position().distanceFrom(position) < b->get_position().distanceFrom(position); }
	);

	return (it == m_nodes.end()) ? nullptr : *it;
}

Node* Field::get_node(const Vec2 & position) const
{
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(), [position](Node* n) { return n->get_position() == position; });

	return (it == m_nodes.end()) ? nullptr : *it;
}

void Field::update()
{
	m_camera->update();

	{
		auto t = m_camera->create_transformer();

		draw_roads(Node::s_radius * 1.0, ColorF(Palette::Green));
		draw_roads(Node::s_radius * 0.5, Palette::Khaki);

		/*
		for (auto* n : m_nodes)
		{
			Circle(n->get_position(), Node::s_radius)
				.draw(ColorF(Palette::Gray, 0.25));

			Circle(n->get_position(), Node::s_radius * 0.5)
				.draw(ColorF(Palette::Gray, 0.5))
				.drawFrame(1.0, Palette::Black);
		}
		*/

		for (auto* b : m_buildings)
		{
			auto color = Palette::White;

			b->get_texture()
				.rotated(b->get_rotation())
				.drawAt(b->get_position(), color);

			b->get_shape().drawFrame(1, ColorF(color, 0.75));

			b->get_site().drawFrame(1, ColorF(color, 0.50));

			//Devices
			for (auto* e : b->get_devices())
			{
				e->get_texture()
					.rotated(e->get_rotation())
					.drawAt(e->get_position());

				e->get_shape()
					.drawFrame();
			}

			Circle(b->get_entrance()->get_position(), Node::s_radius)
				.draw(ColorF(1.0, 0.25))
				.drawFrame(1.0, ColorF(1.0, 1.0));
		}
	}

	if (m_builder != nullptr) { m_builder->update(); }

	m_menu->update();
}

void Field::draw_roads(double width, Color color)
{
	Array<Path*> paths;

	for (auto* r : m_roads)
	{
		paths.emplace_back(r->get_primary());
		paths.emplace_back(r->get_secondary());
	}
	
	for(auto p1 : paths)
	{
		for (auto* p2 : p1->get_from()->get_paths())
		{
			auto l1 = p1->get_line();
			auto l2 = p2->get_line();
			auto v1 = l1.vector().normalized();
			auto v2 = l2.vector().normalized();
			auto theta = Abs(v1.getAngle(v2)) / 2.0;
			auto len = Node::s_radius  / Sin(theta);
			auto n1 = l1.begin + (l1.vector().setLength(Node::s_radius  / Tan(theta)));
			auto n2 = l2.begin + (l2.vector().setLength(Node::s_radius  / Tan(theta)));

			if (v1.cross(v2) < 0)
			{
				Circle(l1.begin + (v1 + v2).setLength(len), Node::s_radius  - width / 2.0)
					.drawArc(Circular0(v1).theta + Math::HalfPi, Math::Pi - theta * 2, 0, width, color);
			}
			else
			{
				Circle(l1.begin + (v1 + v2).setLength(len), Node::s_radius  - width / 2.0)
					.drawArc(Circular0(v2).theta + Math::HalfPi, Math::Pi - theta * 2, 0, width, color);
			}

			Line(l1.center(), n1)
				.stretched(-width * 0.5)
				.draw(width, color);
		}
	}
}


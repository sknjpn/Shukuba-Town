#include "Field.h"
#include "Builder.h"
#include "Camera.h"
#include "Menu.h"
#include "Node.h"
#include "Path.h"
#include "Road.h"
#include "Building.h"
#include "Equipment.h"

#include "Builder_Road.h"
#include "Builder_Building.h"

Field* g_field = nullptr;

Field::Field()
	: m_json(U"data/data.json")
	, m_builder(nullptr)
	, m_camera(new Camera)
	, m_menu(new Menu)
{

}


Field::~Field()
{
	delete m_camera;
	delete m_menu;
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

		for (auto* n : m_nodes)
		{
			Circle(n->get_position(), Node::s_radius).draw(Palette::White);
		}

		for (auto* r : m_roads)
		{
			r->get_line().stretched(-Node::s_radius).draw(Node::s_radius * 2.0);
		}

		for (auto* r : m_roads)
		{
			Vec2 head = Vec2::One() * Node::s_radius * 0.5;

			{
				auto l = r->get_primary()->get_line();

				l.movedBy(l.vector().setLength(Node::s_radius / 2.0).rotated(Math::HalfPi))
					.stretched(-Node::s_radius * 0.5)
					.drawArrow(Node::s_radius / 4.0, head, Palette::Red);
			}

			{
				auto l = r->get_secondary()->get_line();

				l.movedBy(l.vector().setLength(Node::s_radius / 2.0).rotated(Math::HalfPi))
					.stretched(-Node::s_radius * 0.5)
					.drawArrow(Node::s_radius / 4.0, head, Palette::Red);
			}
		}

		for (auto* n : m_nodes)
		{
			Circle(n->get_position(), Node::s_radius)
				.draw(ColorF(Palette::Gray, 0.25));

			Circle(n->get_position(), Node::s_radius * 0.5)
				.draw(ColorF(Palette::Gray, 0.5))
				.drawFrame(1.0, Palette::Black);
		}

		for (auto* b : m_buildings)
		{
			auto color = Palette::White;

			b->get_texture()
				.rotated(b->get_rotation())
				.drawAt(b->get_position(), color);

			b->get_shape().drawFrame(1, ColorF(color, 0.75));

			b->get_site().drawFrame(1, ColorF(color, 0.50));

			//Equipments
			for (auto* e : b->get_equipments())
			{
				e->get_texture()
					.rotated(e->get_rotation())
					.drawAt(e->get_position());

				e->get_shape()
					.drawFrame();
			}

			Circle(b->get_position().rotated(b->get_rotation()), Node::s_radius)
				.draw(ColorF(1.0, 0.25))
				.drawFrame(1.0, ColorF(1.0, 1.0));
		}
	}

	if (m_builder != nullptr) { m_builder->update_samples(); m_builder->update(); }

	m_menu->update();
}


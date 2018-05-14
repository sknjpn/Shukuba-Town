#include "Field.h"
#include "Builder.h"
#include "Camera.h"
#include "Node.h"
#include "Path.h"

#include "Builder_Road.h"

Field* g_field = nullptr;

Field::Field()
{
	m_camera = new Camera;

	m_builder = new Builder_Road;
}


Field::~Field()
{
	delete m_camera;
}

Path* Field::get_closest_path(const Vec2 & position) const
{
	auto it = std::min_element(
		m_paths.begin(),
		m_paths.end(),
		[&position](Path* a, Path* b) { return Geometry2D::Distance(a->get_line(), position) < Geometry2D::Distance(b->get_line(), position); }
	);

	return (it == m_paths.end()) ? nullptr : *it;
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
	m_builder->update();

	{
		auto t = m_camera->create_transformer();

		for (auto* p : m_paths)
		{
			p->draw();
		}
	}
}


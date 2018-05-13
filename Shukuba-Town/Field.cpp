#include "Field.h"
#include "Camera.h"
#include "Node.h"

Field* g_field = nullptr;

Field::Field()
{
	m_camera = new Camera();
}


Field::~Field()
{
	delete m_camera;
}

Node* Field::get_node(const Vec2 & position) const
{
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(), [position](Node* n) { return n->get_position() == position; });

	return (it == m_nodes.end()) ? nullptr : *it;
}


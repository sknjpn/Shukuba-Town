#include "Node.h"
#include "Path.h"
#include "Field.h"

const double Node::s_radius = 16.0;

Node::Node(const Vec2& position)
	: Transform(position)
{
	//field‚É“o˜^
	g_field->add_node(this);
}

Node::~Node()
{
	g_field->remove_node(this);
}

bool Node::has_path(Node* to) const
{
	return m_paths.end() != std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; });
}

Path* Node::get_path(Node* to) const
{
	return has_path(to) ? *std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }) : nullptr;
}

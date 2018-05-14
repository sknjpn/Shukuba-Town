#include "Node.h"
#include "Path.h"
#include "Field.h"

Node::Node(const Vec2& position, double radius)
	: Transform(position), m_radius(radius)
{
	//field‚É“o˜^
	g_field->add_node(this);
}

Node::~Node()
{
	g_field->remove_node(this);
}

void Node::connect(Node* to, double width)
{
	this->m_paths.emplace_back(new Path(this, to, width));
	to->m_paths.emplace_back(new Path(to, this, width));
}

void Node::disconnect(Node* to)
{
	this->m_paths.remove_if([to](Path* p) { return p->get_to() == to; });
	to->m_paths.remove_if([this](Path* p) { return p->get_to() == this; });
}

bool Node::has_path(Node* to) const
{
	return m_paths.end() != std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; });
}

Path* Node::get_path(Node* to) const
{
	return has_path(to) ? *std::find_if(m_paths.begin(), m_paths.end(), [to](Path* p) { return p->get_to() == to; }) : nullptr;
}

#include "Node.h"
#include "Path.h"
#include "Field.h"

Node::Node(const Vec2& position, double radius)
	: Transform(position), m_radius(radius)
{
	//field�ɓo�^
	g_field->add_node(this);
}

Node::~Node()
{
	g_field->remove_node(this);
}

void Node::connect(Node * to, double width)
{
	m_paths.emplace_back(new Path(this, to, width)); to->m_paths.emplace_back(new Path(to, this, width));
}

void Node::disconnect(Node * to)
{
	m_paths.remove_if([to](Path* p) { return p->get_to() == to; }); to->m_paths.remove_if([this](Path* p) { return p->get_to() == this; });
}
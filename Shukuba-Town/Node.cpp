#include "Node.h"
#include "Field.h"

Node::Node(const Vec2& position)
	: Transform(position) 
{
	//field�ɓo�^
	g_field->add_node(this);
}

Node::~Node()
{
	g_field->remove_node(this);
}

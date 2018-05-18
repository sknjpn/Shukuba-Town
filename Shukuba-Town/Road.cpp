#include "Road.h"
#include "Node.h"
#include "Path.h"
#include "Field.h"

Road::Road(Node* from, Node* to)
	: m_from(from)
	, m_to(to)
{
	m_primary = new Path(from, to);
	m_secondary = new Path(to, from);

	g_field->add_road(this);
}

Road::~Road()
{
	g_field->remove_road(this);
}

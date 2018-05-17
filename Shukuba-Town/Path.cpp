#include "Path.h"
#include "Node.h"
#include "Field.h"

Path::Path(Node* from, Node* to)
	: m_from(from), m_to(to)
{
	g_field->add_path(this);
}

Path::~Path()
{
	g_field->remove_path(this);
}

Path* Path::get_opposite() const
{
	return m_to->get_path(m_from);
}

Line Path::get_line() const
{
	return Line(m_from->get_position(), m_to->get_position());
}
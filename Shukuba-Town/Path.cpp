#include "Path.h"
#include "Node.h"
#include "Field.h"

Path::Path(Node* from, Node* to, double width)
	: m_from(from), m_to(to), m_width(width)
{
	g_field->add_path(this);
}

Path::~Path()
{
	g_field->remove_path(this);
}

Path* Path::get_opposite() const
{
	return m_from->get_path(m_to);
}

Line Path::get_line() const
{
	return Line(m_from->get_position(), m_to->get_position());
}

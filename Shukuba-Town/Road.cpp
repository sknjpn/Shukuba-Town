#include "Road.h"
#include "Node.h"
#include "Path.h"
#include "Field.h"

Road::Road(Node* from, Node* to)
	: m_from(from)
	, m_to(to)
{
	m_primary = new Path(this, from, to);
	m_secondary = new Path(this, to, from);

	from->m_paths.emplace_back(m_primary);
	to->m_paths.emplace_back(m_secondary);

	g_field->add_road(this);
}

Road::~Road()
{
	m_from->m_paths.remove(m_primary);
	m_to->m_paths.remove(m_secondary);

	delete m_primary;
	delete m_secondary;

	g_field->remove_road(this);
}

Line Road::get_line() const
{
	return Line(m_from->get_position(), m_to->get_position());
}


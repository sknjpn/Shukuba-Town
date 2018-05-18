#include "Road.h"
#include "Node.h"
#include "Path.h"

Road::Road(Node* from, Node* to)
	: m_from(from)
	, m_to(to)
{
	m_primary = new Path(from, to);
	m_secondary = new Path(to, from);
}

#include "Path.h"
#include "Field.h"

Path::Path(Node * from, Node * to)
	: m_from(from), m_to(to) 
{
	g_field->add_path(this);
}

Path::~Path()
{
	g_field->remove_path(this);
}

#include "Field.h"
#include "Camera.h"

Field* g_field = nullptr;

Field::Field()
{
	m_camera = new Camera();
}


Field::~Field()
{
	delete m_camera;
}

#include "Building.h"

Building::Building()
{

}

void Building::draw()
{
	m_texture
		.rotated(get_rotation())
		.drawAt(get_position());
}

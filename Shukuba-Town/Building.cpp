#include "Building.h"
#include "Factory.h"
#include "Field.h"
#include "Device.h"
#include "Node.h"

void Building::init_jobs(JSONValue json)
{
	for (auto j : json[U"devices"].arrayView())
	{
		auto position = j[U"position"].get<Position>().rotated(get_rotation()) + get_position();
		auto rotation = j[U"rotation"].get<Rotation>() + get_rotation();

		m_devices.emplace_back(Factory::make_device(position, rotation, j));
	}
}

void Building::init_devices(JSONValue json)
{
	if (json[U"jobs"].isEmpty())
	{
		m_jobs.emplace_back(Factory::make_job(this, json[U"jobs"]));
	}
}

Building::Building(Node* entrance, const Rotation& rotation, JSONValue json)
	: Transform(entrance->get_position(), rotation)
	, m_entrance(entrance)
{
	g_field->add_building(this);

	Image	image_shape(json[U"texture"][U"shape"].get<FilePath>());
	Image	image_site(json[U"texture"][U"site"].get<FilePath>());

	m_texture = Texture(image_shape);

	m_base_shape = ImageProcessing::FindExternalContour(image_shape, true)
		.movedBy(Vec2::One() / 2.0)
		.movedBy(-image_shape.size() / 2.0)
		.calculateRoundBuffer(16.0);

	m_base_site = ImageProcessing::FindExternalContour(image_site, true)
		.movedBy(Vec2::One() / 2.0)
		.movedBy(-image_site.size() / 2.0);

	init_devices(json);
	init_jobs(json);
}

Building::~Building()
{
	g_field->remove_building(this);
}
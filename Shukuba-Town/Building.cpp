#include "Building.h"
#include "Factory.h"
#include "Field.h"
#include "Equipment.h"
#include "Node.h"

void Building::init_jobs(JSONValue json)
{
	for (auto j : json[U"equipments"].arrayView())
	{
		auto position = j[U"position"].get<Position>().rotated(get_rotation()) + get_position();
		auto rotation = j[U"rotation"].get<Rotation>() + get_rotation();

		m_equipments.emplace_back(Factory::make_equipment(position, rotation, j));
	}
}

void Building::init_equipments(JSONValue json)
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

	init_equipments(json);
	init_jobs(json);
}

Building::~Building()
{
	g_field->remove_building(this);
}

void Building::draw() const
{
	auto color = Palette::White;

	m_texture
		.rotated(get_rotation())
		.drawAt(get_position(), color);

	get_shape().drawFrame(1, ColorF(color, 0.75));

	get_site().drawFrame(1, ColorF(color, 0.50));

	//Equipments
	for (auto* e : m_equipments) { e->draw(); }

	Circle(get_position().rotated(get_rotation()), 32.0)
		.draw(ColorF(1.0, 0.25))
		.drawFrame(1.0, ColorF(1.0, 1.0));
}
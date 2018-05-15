#include "Building.h"
#include "Factory.h"
#include "Field.h"
#include "Equipment.h"

void Building::init_jobs(s3d::JSONValue json)
{
	for (auto j : json[U"equipments"].arrayView())
	{
		auto position = j[U"position"].get<Position>().rotated(get_rotation()) + get_position();
		auto rotation = j[U"rotation"].get<Rotation>() + get_rotation();

		m_equipments.emplace_back(Factory::make_equipment(position, rotation, j));
	}
}

void Building::init_equipments(s3d::JSONValue json)
{
	if (json[U"jobs"].isEmpty())
	{
		m_jobs.emplace_back(Factory::make_job(this, json[U"jobs"]));
	}
}

Building::Building(const Position& position, const Rotation& rotation, s3d::JSONValue json)
	: Transform(position, rotation)
	, m_entrance(json[U"entrance"].get<Position>())
{
	s3d::Image	image_shape(json[U"texture"][U"shape"].get<s3d::FilePath>());
	s3d::Image	image_site(json[U"texture"][U"site"].get<s3d::FilePath>());

	m_texture = s3d::Texture(image_shape);

	m_base_shape = s3d::ImageProcessing::FindExternalContour(image_shape, true)
		.movedBy(s3d::Vec2::One() / 2.0)
		.movedBy(-image_shape.size() / 2.0)
		.calculateRoundBuffer(16.0);

	m_base_site = s3d::ImageProcessing::FindExternalContour(image_site, true)
		.movedBy(s3d::Vec2::One() / 2.0)
		.movedBy(-image_site.size() / 2.0);

	init_equipments(json);
	init_jobs(json);
}

void Building::draw() const
{
	auto color = s3d::Palette::White;

	m_texture
		.rotated(get_rotation())
		.drawAt(get_position(), color);

	get_shape().drawFrame(1, s3d::ColorF(color, 0.75));

	get_site().drawFrame(1, s3d::ColorF(color, 0.50));

	//Equipments
	for (const auto* e : m_equipments) { e->draw(); }

	s3d::Circle(get_position() + m_entrance.get_position().rotated(get_rotation()), 32.0)
		.draw(s3d::ColorF(1.0, 0.25))
		.drawFrame(1.0, s3d::ColorF(1.0, 1.0));
}

void Building::Entrance::update_connection()
{
	m_node = nullptr;

	const auto& roads = g_village->get_roads();

	auto it = std::min_element(
		roads.begin(),
		roads.end(),
		[this](Road* a, Road* b) {return a->get_distance_from(get_position()) < b->get_distance_from(get_position()); }
	);

	if (it != roads.end() && (*it)->get_distance_from(get_position()) < 32.0)
	{
		m_node = new Junction(*it, (*it)->get_from()->get_position().distanceFrom((*it)->get_closest(get_position())));
	}
}
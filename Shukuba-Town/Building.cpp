#include "Building.h"

namespace skn
{
	void Building::init_jobs(s3d::JSONValue json)
	{

	}

	void Building::init_equipments(s3d::JSONValue json)
	{
		json[U"jobs"].
	}

	Building::Building(s3d::JSONValue json)
		: m_entrance(json[U"entrance"].get<s3d::Vec2>())
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
	}

	s3d::Polygon Building::get_shape() const
	{
		return m_base_shape
			.rotated(get_rotation())
			.movedBy(get_position());
	}

	s3d::Polygon Building::get_site() const
	{
		return m_base_site
			.rotated(get_rotation())
			.movedBy(get_position());
	}

	const std::vector<Equipment*>& Building::get_equipments() const
	{
		return m_equipments;
	}

	void Building::add_equipment(Equipment* equipment)
	{
		m_equipments.emplace_back(equipment);
	}

	void Building::draw() const
	{
		auto color = s3d::Palette::White;

		m_texture
			.rotated(get_rotation())
			.drawAt(get_position(), color);

		get_shape().drawFrame(1, s3d::ColorF(color, 0.75));

		get_site().drawFrame(1, s3d::ColorF(color, 0.50));

		s3d::Circle(get_position() + m_entrance.rotated(get_rotation()), 32.0)
			.draw(s3d::ColorF(1.0, 0.25))
			.drawFrame(1.0, s3d::ColorF(1.0, 1.0));
	}
}
#pragma once

#include "Sample.h"
#include "Transform.h"

class Sample_Building
	: public Sample
{
	Texture		m_texture;
	Polygon		m_base_shape;
	Polygon		m_base_site;
	Position	m_entrance;
	JSONValue	m_json;

public:
	Sample_Building(const RectF& rect, JSONValue json)
		: Sample(rect, Texture(json[U"texture"][U"shape"].get<FilePath>()))
		, m_json(json)
		, m_entrance(json[U"entrance"].get<Position>())
	{
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
	}

	//getter
	Texture			get_texture() const { return m_texture; }
	const Polygon&	get_base_shape() const { return m_base_shape; }
	const Polygon&	get_base_site() const { return m_base_site; }
	const Position&	get_entrance() const { return m_entrance; }
	JSONValue		get_json() const { return m_json; }
};


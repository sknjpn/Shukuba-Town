#include "Equipment.h"
#include "Building.h"

namespace skn
{
	Equipment::Equipment(const Position& position, const Rotation& rotation, s3d::JSONValue json)
		: Transform(position, rotation)
	{
		//shape
		{
			s3d::Image image(json[U"texture"].get<s3d::FilePath>());

			m_texture = s3d::Texture(image);

			m_base_shape = s3d::ImageProcessing::FindExternalContour(image, true)
				.movedBy(s3d::Vec2::One() / 2.0)
				.movedBy(-image.size() / 2.0);
		}
	}

	void Equipment::draw() const
	{
		m_texture
			.rotated(get_rotation())
			.drawAt(get_position());

		get_shape()
			.drawFrame();
	}
}
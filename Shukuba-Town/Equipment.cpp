#include "Equipment.h"
#include "Building.h"

Equipment::Equipment(const Position& position, const Rotation& rotation, JSONValue json)
	: Transform(position, rotation)
{
	//shape
	{
		Image image(json[U"texture"].get<FilePath>());

		m_texture = Texture(image);

		m_base_shape = ImageProcessing::FindExternalContour(image, true)
			.movedBy(Vec2::One() / 2.0)
			.movedBy(-image.size() / 2.0);
	}
}
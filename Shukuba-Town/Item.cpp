#include "Item.h"

namespace skn
{
	Item::Item(s3d::JSONValue json)
		: m_name(json[U"name"].getString())
		, m_weight(json[U"weight"].get<int>())
		, m_texture(json[U"texture"].getString())
	{
		
	}

	s3d::String Item::get_name() const
	{
		return m_name;
	}

	s3d::Texture Item::get_texture() const
	{
		return m_texture;
	}

	int Item::get_weight() const
	{
		return m_weight;
	}
}
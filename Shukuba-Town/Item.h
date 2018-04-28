#pragma once

namespace skn
{
	class Item
	{
		s3d::String		m_name;
		s3d::Texture	m_texture;
		int				m_weight;

	public:
		Item(s3d::JSONValue json);
		virtual ~Item() = default;

		s3d::String		get_name() const;
		s3d::Texture	get_texture() const;
		int				get_weight() const;
	};
}
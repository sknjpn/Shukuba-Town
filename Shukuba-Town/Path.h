#pragma once

#include "Uncopyable.h"

namespace skn
{
	class Node;

	class Path
		: Uncopyable
	{
		double	m_length;
		double	m_width;
		Node*	m_from;
		Node*	m_to;

		//ê}å`
		s3d::Line		m_line;
		s3d::Polygon	m_shape;

	public:
		Path(Node* from, Node* to, double width);

		void		disconnect();

		bool		intersects(const s3d::Vec2& position) const;
		bool		intersects(const s3d::Circle& circle) const;

		double		get_distance_from(const Path* other) const;
		double		get_distance_from(const s3d::Line& line) const;
		double		get_distance_from(const s3d::Vec2& position) const;

		bool		has(const Node* node) const;

		Node*		get_opposite(const Node* node) const;
		Node*		get_from() const;
		Node*		get_to() const;
		double		get_width() const;
		double		get_length() const;
		s3d::Vec2	get_closest(const s3d::Vec2& position) const;

		const s3d::Line&	get_line() const;

		void		draw() const;
	};
}
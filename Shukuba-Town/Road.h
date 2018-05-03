#pragma once

#include "Transform.h"
#include "Uncopyable.h"

namespace skn
{
	class Path;
	class Junction;

	class Anchor
		: public Transform
	{

	};

	class Node
		: public Transform
		, public Uncopyable
	{
		friend Junction;

		double		m_radius;
		std::vector<Path*>	m_paths;

		//’Tõ—p
		Path*		m_use_path;
		bool		m_added;
		double		m_cost;

	public:
		Node(const s3d::Vec2& position, double radius);

		double		get_radius() const { return m_radius; }

		Path*		get_path(Node* other) const;

		void		connect(Node* other, double width);
		void		disconnect(Node* other);
	};

	class Path
		: public Uncopyable
	{
		double	m_length;
		double	m_width;
		Node*	m_from;
		Node*	m_to;

		//}Œ`
		s3d::Line		m_line;
		s3d::Polygon	m_shape;

	public:
		Path(Node* from, Node* to, double width);

		//getter
		Node*		get_from() const { return m_from; }
		Node*		get_to() const { return m_to; }
		double		get_width() const { return m_width; }
		double		get_length() const { return m_length; }

		void		disconnect() { m_from->disconnect(m_to); }

		double		get_distance_from(const Path* other) const{ return get_distance_from(other->m_line); }
		double		get_distance_from(const s3d::Line& line) const;
		double		get_distance_from(const s3d::Vec2& position) const { return get_closest(position).distanceFrom(position); }

		bool		has(const Node* node) const { return node == m_from || node == m_to; }
		Node*		get_opposite(const Node* node) const { return (node == m_from) ? m_to : m_from; }

		s3d::Vec2	get_closest(const s3d::Vec2& position) const { return m_line.closest(position); }

		const s3d::Line&	get_line() const { return m_line; }

		void		draw() const;
	};

	class Junction
		: public Transform
	{
		Node*	m_node;
		Path*	m_path;
		double	m_t;

	public:
		Junction(Node* node);
		Junction(Path* path, double t);

		std::vector<Junction>	make_route(const Junction& target) const;
	};
}
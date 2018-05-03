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
	public:
		Anchor(const Position& position) : Transform(position) {}
	};

	class Rope
	{
		Anchor*	m_anchor_from;
		Anchor*	m_anchor_to;
		double	m_width;

	public:
		Rope(Anchor* from, Anchor* to, double width) : m_anchor_from(from), m_anchor_to(to), m_width(width) {}

		double	get_width() const { return m_width; }
	};

	class Node
		: public Anchor
	{
		friend Junction;

		double		m_radius;
		std::vector<Path*>	m_paths;

		//�T���p
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

		//�}�`
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

		double		get_distance_from(const Path* other) const { return get_distance_from(other->m_line); }
		double		get_distance_from(const s3d::Line& line) const;
		double		get_distance_from(const s3d::Vec2& position) const { return get_closest(position).distanceFrom(position); }

		bool		has(const Node* node) const { return node == m_from || node == m_to; }
		Node*		get_opposite(const Node* node) const { return (node == m_from) ? m_to : m_from; }

		s3d::Vec2	get_closest(const s3d::Vec2& position) const { return m_line.closest(position); }

		const s3d::Line&	get_line() const { return m_line; }

		void		draw() const;
	};

	class Junction
		: public Anchor
	{
		Path*	m_path;
		double	m_t;

	public:
		Junction(Path* path, double t);

		std::vector<Anchor*>	make_route(Anchor* target) const;
	};
}
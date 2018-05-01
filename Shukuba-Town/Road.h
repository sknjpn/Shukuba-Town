#pragma once

#include "Transform.h"

namespace skn
{
	class Path;

	class Node
		: public Transform
	{
		double		m_radius;
		std::vector<Path*>	m_paths;

		//íTçıóp
		Path*		m_use_path;
		bool		m_added;
		double		m_cost;

	public:
		Node(const s3d::Vec2& position, double radius);

		double		get_radius() const;

		Path*		get_path(Node* other) const;

		void		connect(Node* other, double width);
		void		disconnect(Node* other);

		std::vector<Node*>	make_route(Node* target);

		const std::vector<Path*>&	get_paths() const;
	};

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

	class Junction
		: public Transform
	{
		Node*	m_node;
		Path*	m_path;
		double	m_t;

	public:
		Junction(Node* node);
		Junction(Path* path, double t);
	};
}
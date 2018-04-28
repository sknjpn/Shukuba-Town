#pragma once

#include "Uncopyable.h"
#include "Transform.h"

namespace skn
{
	class Path;

	class Node
		: public Transform
	{
		std::vector<Path*>	m_paths;

		//�T���p
		Path*		m_use_path;
		bool		m_added;
		double		m_cost;
		double		m_radius;

	public:
		Node(const s3d::Vec2& position, double radius);

		double		get_radius() const;

		double		get_distance_from(const s3d::Vec2& position) const;
		Path*		get_path(Node* other) const;
		
		void		connect(Node* other, double width);
		void		disconnect(Node* other);
		
		std::vector<Node*>	make_route(Node* target);

		const std::vector<Path*>&	get_paths() const;
	};
}
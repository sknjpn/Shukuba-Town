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
}
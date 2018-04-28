#include "Node.h"
#include "Path.h"
#include "Village.h"

namespace skn
{
	Node::Node(const s3d::Vec2& position, double radius)
		: Transform(position)
		, m_radius(radius)
		, m_use_path(nullptr)
		, m_added(false)
		, m_cost(0.0)
	{

	}

	double Node::get_radius() const
	{
		return m_radius;
	}

	const std::vector<Path*>& Node::get_paths() const
	{
		return m_paths;
	}

	double Node::get_distance_from(const s3d::Vec2& position) const
	{
		return std::max(0.0, position.distanceFrom(get_position()) - get_radius());
	}

	Path* Node::get_path(Node* other) const
	{
		auto it = std::find_if(
			m_paths.begin(), 
			m_paths.end(), 
			[other, this](Path* p) { return p->get_opposite(this) == other; }
		);

		return (it == m_paths.end()) ? nullptr : *it;
	}

	void Node::connect(Node* other, double width)
	{
		auto* path = g_village->add_path(new Path(this, other, width));

		this->m_paths.emplace_back(path);
		other->m_paths.emplace_back(path);
	}

	void Node::disconnect(Node* other)
	{
		auto path = get_path(other);

		if (path == nullptr) { LOG_ERROR(U"çÌèúëŒè€ÇÃê⁄ë±Ç™Ç†ÇËÇ‹ÇπÇÒ"); return; }

		this->m_paths.erase(std::find(this->m_paths.begin(), this->m_paths.end(), path));
		other->m_paths.erase(std::find(other->m_paths.begin(), other->m_paths.end(), path));

		g_village->delete_path(path);
	}

	std::vector<Node*>	Node::make_route(Node* target)
	{
		std::vector<Node*> result;

		if (target == this) { return result; }

		//èâä˙âª
		for (auto* n : g_village->get_nodes())
		{
			n->m_cost = 0;
			n->m_added = false;
			n->m_use_path = nullptr;
		}

		s3d::Array<Node*> nodes{ target };
		target->m_cost = 1;

		for (size_t i = 0; i < nodes.size(); i++)
		{
			auto* n1 = nodes[i];

			n1->m_added = false;

			for (auto* p : n1->m_paths)
			{
				auto* n2 = p->get_opposite(n1);

				if (n2->m_cost == 0 || n2->m_cost > n1->m_cost + p->get_length())
				{
					n2->m_cost = n1->m_cost + p->get_length();
					n2->m_use_path = n2->get_path(n1);

					if (!n2->m_added)
					{
						nodes.emplace_back(n2);
						n2->m_added = true;
					}
				}
			}
		}

		//ê⁄ë±Ç™Ç»Ç©Ç¡ÇΩèÍçá
		if (m_cost == 0) { result; }

		std::vector<Path*> paths;

		auto* node = this;

		while (node->m_use_path != nullptr)
		{
			paths.emplace_back(node->m_use_path);

			node = node->m_use_path->get_opposite(node);
		}

		return result;
	}
}
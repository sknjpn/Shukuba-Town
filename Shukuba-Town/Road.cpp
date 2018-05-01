#include "Road.h"
#include "Village.h"

namespace skn
{
	Path::Path(Node* from, Node* to, double width)
		: m_from(from)
		, m_to(to)
		, m_width(width)
		, m_line(from->get_position(), to->get_position())
		, m_length(from->get_position().distanceFrom(to->get_position()))
	{
		auto p1 = m_from->get_position();
		auto p2 = m_to->get_position();
		auto vector = (p1 - p2).setLength(m_width / 2.0).rotated(s3d::Math::HalfPi);

		s3d::Array<s3d::Vec2> points{ p1 - vector, p1 + vector, p2 + vector, p2 - vector, };

		m_shape = s3d::Polygon(points);
		m_shape.append(s3d::Circle(p1, m_width / 2.0).asPolygon());
		m_shape.append(s3d::Circle(p2, m_width / 2.0).asPolygon());
	}

	void Path::disconnect()
	{
		m_from->disconnect(m_to);
	}

	double Path::get_width() const
	{
		return m_width;
	}

	double Path::get_length() const
	{
		return m_length;
	}

	double Path::get_distance_from(const Path* other) const
	{
		return get_distance_from(other->m_line);
	}

	double Path::get_distance_from(const s3d::Line& line) const
	{
		return std::max(0.0, std::min({
			m_line.begin.distanceFrom(line.begin),
			m_line.begin.distanceFrom(line.end),
			m_line.end.distanceFrom(line.begin),
			m_line.end.distanceFrom(line.end),
			}));
	}

	double Path::get_distance_from(const s3d::Vec2& position) const
	{
		return std::max(0.0, get_closest(position).distanceFrom(position));
	}

	s3d::Vec2 Path::get_closest(const s3d::Vec2& position) const
	{
		return m_line.closest(position);
	}

	void Path::draw() const
	{
		m_shape.draw(s3d::Palette::Khaki);
	}

	bool Path::intersects(const s3d::Vec2& position) const
	{
		return get_closest(position).distanceFrom(position) <= m_width / 2.0;
	}

	bool Path::intersects(const s3d::Circle& circle) const
	{
		return get_closest(circle.center).distanceFrom(circle.center) <= m_width / 2.0 + circle.r;
	}

	bool Path::has(const Node* node) const
	{
		return m_from == node || m_to == node;
	}

	Node* Path::get_opposite(const Node* node) const
	{
		return (node == m_from) ? m_to : m_from;
	}

	Node* Path::get_from() const
	{
		return m_from;
	}

	Node* Path::get_to() const
	{
		return m_to;
	}

	const s3d::Line& Path::get_line() const
	{
		return m_line;
	}
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

	Junction::Junction(Node* node)
		: Transform(node->get_position())
		, m_node(node)
		, m_path(nullptr)
		, m_t(0)
	{

	}

	Junction::Junction(Path* path, double t)
		: Transform(path->get_from()->get_position() + (path->get_to()->get_position() - path->get_from()->get_position()).setLength(t))
		, m_node(nullptr)
		, m_path(path)
		, m_t(t)
	{

	}
}
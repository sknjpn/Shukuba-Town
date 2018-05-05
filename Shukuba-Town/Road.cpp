#include "Road.h"
#include "Village.h"

namespace skn
{
	Road::Road(Node* from, Node* to, double width)
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

	double Road::get_distance_from(const s3d::Line& line) const
	{
		return std::min({
			m_line.begin.distanceFrom(line.begin),
			m_line.begin.distanceFrom(line.end),
			m_line.end.distanceFrom(line.begin),
			m_line.end.distanceFrom(line.end),
			});
	}

	void Road::draw() const
	{
		m_shape.draw(s3d::Palette::Khaki);
	}

	Node::Node(const s3d::Vec2& position, double radius)
		: Anchor(position)
		, m_radius(radius)
		, m_use_road(nullptr)
		, m_added(false)
		, m_cost(0.0)
	{

	}

	Road* Node::get_road(Node* other) const
	{
		auto it = std::find_if(
			m_roads.begin(),
			m_roads.end(),
			[other, this](Road* p) { return p->get_opposite(this) == other; }
		);

		return (it == m_roads.end()) ? nullptr : *it;
	}

	void Node::connect(Node* other, double width)
	{
		auto* road = g_village->add_road(new Road(this, other, width));

		this->m_roads.emplace_back(road);
		other->m_roads.emplace_back(road);
	}

	void Node::disconnect(Node* other)
	{
		auto road = get_road(other);

		if (road == nullptr) { LOG_ERROR(U"íœ‘ÎÛ‚ÌÚ‘±‚ª‚ ‚è‚Ü‚¹‚ñ"); return; }

		this->m_roads.erase(std::find(this->m_roads.begin(), this->m_roads.end(), road));
		other->m_roads.erase(std::find(other->m_roads.begin(), other->m_roads.end(), road));

		g_village->delete_road(road);
	}

	Junction::Junction(Road* road, double t)
		: Anchor(road->get_from()->get_position() + (road->get_to()->get_position() - road->get_from()->get_position()).setLength(t))
		, m_road(road)
		, m_t(t)
	{

	}

	std::vector<Anchor*> Junction::make_route(Anchor* target) const
	{
		std::vector<Anchor*> result;

		if (target == this) { return result; }

		/*
		//‰Šú‰»
		for (auto* n : g_village->get_nodes())
		{
			n->m_cost = 0;
			n->m_added = false;
			n->m_use_road = nullptr;
		}

		s3d::Array<Node*> nodes;
		if (target->m_node != nullptr)
		{
			nodes.emplace_back(target->m_node);
			target->m_node->m_cost = 1;
		}
		else
		{
			auto* nf = target->m_road->get_from();
			auto* nt = target->m_road->get_to();

			nodes.emplace_back(nf);
			nf->m_cost = 1 + target->get_position().distanceFrom(nf->get_position());

			nodes.emplace_back(nt);
			nt->m_cost = 1 + target->get_position().distanceFrom(nt->get_position());
		}

		for (size_t i = 0; i < nodes.size(); i++)
		{
			auto* n1 = nodes[i];

			n1->m_added = false;

			for (auto* p : n1->m_roads)
			{
				auto* n2 = p->get_opposite(n1);

				if (n2->m_cost == 0 || n2->m_cost > n1->m_cost + p->get_length())
				{
					n2->m_cost = n1->m_cost + p->get_length();
					n2->m_use_road = n2->get_road(n1);

					if (!n2->m_added)
					{
						nodes.emplace_back(n2);
						n2->m_added = true;
					}
				}
			}
		}

		Node* node = nullptr;

		if (m_node != nullptr)
		{
			if (m_node->m_cost == 0) { return result; }

			node = m_node;
		}
		else
		{
			auto* nf = m_road->get_from();
			auto* nt = m_road->get_to();

			if (nf->m_cost == 0) { return result; }

			if (nt->m_cost + get_position().distanceFrom(nt->get_position()) < nf->m_cost + get_position().distanceFrom(nf->get_position()))
			{
				node = nt;
			}
			else
			{
				node = nf;
			}

		}

		std::vector<Road*> roads;

		while (node->m_use_road != nullptr)
		{
			roads.emplace_back(node->m_use_road);

			node = node->m_use_road->get_opposite(node);

			result.emplace_back(node);
		}

		result.emplace_back(target);
		*/
		return result;
	}
}
#include "Path.h"
#include "Node.h"

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

	s3d::Vec2 Path::get_position(double t) const
	{
		return m_from->get_position() + (m_to->get_position() - m_from->get_position()).setLength(t);
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
}
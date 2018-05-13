#pragma once

#include "Drawable.h"

class Node;

class Path final
	: public Uncopyable
	, public Drawable
{
	Node* m_from;
	Node* m_to;
	double m_width;

public:
	Path(Node* from, Node* to, double width);
	~Path();

	Node* get_from() const { return m_from; }
	Node* get_to() const { return m_to; }
	double get_width() const { return m_width; }

	Line get_line() const;

	void draw() override {}
};
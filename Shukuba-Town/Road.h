#pragma once

class Node;
class Path;

class Road
	: public Uncopyable
{
	Node* from;
	Node* to;

	Path* primary;
	Path* secondary;

public:
	Road(Node* from, Node* to);
};


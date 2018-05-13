#pragma once

class Builder;
class Node;

class Field 
	: public Uncopyable
{
	Array<Node*> m_nodes;

	Builder* m_builder;

public:
	Field();
	~Field();
};

extern Field* g_field;
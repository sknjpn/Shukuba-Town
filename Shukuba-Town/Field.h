#pragma once

class Builder;
class Node;
class Path;

class Field 
	: public Uncopyable
{
	Array<Node*> m_nodes;
	Array<Path*> m_paths;

	Builder* m_builder;

public:
	Field();
	~Field();

	void add_node(Node* node) { m_nodes.emplace_back(node); }
	void add_path(Path* path) { m_paths.emplace_back(path); }

	void remove_node(Node* node) { m_nodes.remove(node); }
	void remove_path(Path* path) { m_paths.remove(path); }
};

extern Field* g_field;
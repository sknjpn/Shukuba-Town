#pragma once

class Builder;
class Node;
class Path;
class Building;

class Field 
	: public Uncopyable
{
	Array<Node*> m_nodes;
	Array<Path*> m_paths;
	Array<Building*> m_buildings;

	Builder* m_builder;

public:
	Field();
	~Field();

	void add_node(Node* node) { m_nodes.emplace_back(node); }
	void add_path(Path* path) { m_paths.emplace_back(path); }
	void add_building(Building* building) { m_buildings.emplace_back(building); }

	void remove_node(Node* node) { m_nodes.remove(node); }
	void remove_path(Path* path) { m_paths.remove(path); }
	void remove_building(Building* building) { m_buildings.remove(building); }

	const Array<Node*>& get_nodes() const { return m_nodes; }
	const Array<Path*>& get_paths() const { return m_paths; }
	const Array<Building*>& get_buildings() const { return m_buildings; }
};

extern Field* g_field;
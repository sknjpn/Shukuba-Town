#pragma once

class Builder;
class Node;
class Road;
class Menu;
class Camera;
class Building;

class Field 
	: public Uncopyable
{
	Array<Node*> m_nodes;
	Array<Road*> m_roads;
	Array<Building*> m_buildings;

	Builder*	m_builder;
	Camera*		m_camera;
	Menu*		m_menu;

	JSONReader m_json;

public:
	Field();
	~Field();

	void set_builder(Builder* builder);

	void add_node(Node* node) { m_nodes.emplace_back(node); }
	void add_road(Road* road) { m_roads.emplace_back(road); }
	void add_building(Building* building) { m_buildings.emplace_back(building); }

	void remove_node(Node* node) { m_nodes.remove(node); }
	void remove_road(Road* road) { m_roads.remove(road); }
	void remove_building(Building* building) { m_buildings.remove(building); }

	const Array<Node*>& get_nodes() const { return m_nodes; }
	const Array<Road*>& get_roads() const { return m_roads; }
	const Array<Building*>& get_buildings() const { return m_buildings; }

	Road* get_closest_road(const Vec2& position) const;
	Node* get_closest_node(const Vec2& position) const;

	Node* get_node(const Vec2& position) const;

	Camera* get_camera() const { return m_camera; }

	const JSONReader& get_json() const { return m_json; }

	void update();
};

extern Field* g_field;
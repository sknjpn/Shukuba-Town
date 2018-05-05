#pragma once

#include "Uncopyable.h"

#include "Camera.h"
#include "Clock.h"

namespace skn
{
	class Builder;

	class Item;
	class Node;
	class Road;
	class Agent;
	class Anchor;
	class Building;

	class Village
		: public Uncopyable
	{
		Camera		m_camera;
		Clock		m_clock;

		//基本データ群
		s3d::JSONReader	m_json;

		//このポインタの所有権はVillageが持つ
		Builder*	m_builder;
		std::vector<Item*>		m_items;
		std::vector<Node*>		m_nodes;
		std::vector<Road*>		m_roads;
		std::vector<Agent*>		m_agents;
		std::vector<Anchor*>	m_anchors;
		std::vector<Building*>	m_buildings;

		void		set_builder(Builder* builder);

	public:
		Village();

		Node*		add_node(Node* node) { return m_nodes.emplace_back(node); }
		Road*		add_road(Road* road) { return m_roads.emplace_back(road); }
		Agent*		add_agent(Agent* agent) { return m_agents.emplace_back(agent); }
		Anchor*		add_anchor(Anchor* anchor) { return m_anchors.emplace_back(anchor); }
		Building*	add_building(Building* building) { return m_buildings.emplace_back(building); }

		void		delete_node(Node* node) { m_nodes.erase(std::find(m_nodes.begin(), m_nodes.end(), node)); }
		void		delete_road(Road* road) { m_roads.erase(std::find(m_roads.begin(), m_roads.end(), road)); }
		void		delete_agent(Agent* agent) { m_agents.erase(std::find(m_agents.begin(), m_agents.end(), agent)); }
		void		delete_anchor(Anchor* anchor) { m_anchors.erase(std::find(m_anchors.begin(), m_anchors.end(), anchor)); }
		void		delete_building(Building* building) { m_buildings.erase(std::find(m_buildings.begin(), m_buildings.end(), building)); }

		const std::vector<Item*>&		get_items() const { return m_items; }
		const std::vector<Node*>&		get_nodes() const { return m_nodes; }
		const std::vector<Road*>&		get_roads() const { return m_roads; }
		const std::vector<Agent*>&		get_agents() const { return m_agents; }
		const std::vector<Anchor*>&		get_anchors() const { return m_anchors; }
		const std::vector<Building*>&	get_buildings() const { return m_buildings; }

		Item*		get_item(const s3d::String& name);

		Node*		get_node(const s3d::Vec2& position) const;

		const Camera&	get_camera() const { return m_camera; }

		s3d::JSONValue	get_json() const { return m_json; }

		//Node, Road関連
		Node*		get_closest_node(const s3d::Vec2& position) const;
		Road*		get_closest_road(const s3d::Vec2& position) const;

		void	update();
	};

	extern Village* g_village;
}
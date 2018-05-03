#pragma once

#include "Uncopyable.h"

#include "Camera.h"
#include "Clock.h"

namespace skn
{
	class Builder;

	class Item;
	class Node;
	class Path;
	class Agent;
	class Anchor;
	class Building;
	class Transform;

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
		std::vector<Path*>		m_paths;
		std::vector<Agent*>		m_agents;
		std::vector<Anchor*>	m_anchors;
		std::vector<Building*>	m_buildings;
		std::vector<Transform*>	m_transforms;

		void		set_builder(Builder* builder);

	public:
		Village();

		Node*		add_node(Node* node) { return m_nodes.emplace_back(node); }
		Path*		add_path(Path* path) { return m_paths.emplace_back(path); }
		Agent*		add_agent(Agent* agent) { return m_agents.emplace_back(agent); }
		Building*	add_building(Building* building) { return m_buildings.emplace_back(building); }

		void		delete_node(Node* node) { m_nodes.erase(std::find(m_nodes.begin(), m_nodes.end(), node)); }
		void		delete_path(Path* path) { m_paths.erase(std::find(m_paths.begin(), m_paths.end(), path)); }
		void		delete_agent(Agent* agent) { m_agents.erase(std::find(m_agents.begin(), m_agents.end(), agent)); }
		void		delete_building(Building* building) { m_buildings.erase(std::find(m_buildings.begin(), m_buildings.end(), building)); }

		const std::vector<Item*>&		get_items() const { return m_items; }
		const std::vector<Node*>&		get_nodes() const { return m_nodes; }
		const std::vector<Path*>&		get_paths() const { return m_paths; }
		const std::vector<Agent*>&		get_agents() const { return m_agents; }
		const std::vector<Building*>&	get_buildings() const { return m_buildings; }

		Item*		get_item(const s3d::String& name);

		void		remove_transform(Transform* transform);

		Node*		get_node(const s3d::Vec2& position) const;

		const Camera&	get_camera() const { return m_camera; }

		s3d::JSONValue	get_json() const { return m_json; }

		//Node, Path関連
		Node*		get_closest_node(const s3d::Vec2& position) const;
		Path*		get_closest_path(const s3d::Vec2& position) const;

		void	update();
	};

	extern Village* g_village;
}
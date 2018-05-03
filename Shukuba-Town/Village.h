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

		Node*		add_node(Node* node);
		Path*		add_path(Path* path);
		Agent*		add_agent(Agent* agent);
		Building*	add_building(Building* building);

		Item*		get_item(const s3d::String& name);

		void		delete_node(Node* node);
		void		delete_path(Path* path);
		void		delete_agent(Agent* agent);
		void		delete_building(Building* building);

		void		remove_transform(Transform* transform);

		const std::vector<Item*>&		get_items() const;
		const std::vector<Node*>&		get_nodes() const;
		const std::vector<Path*>&		get_paths() const;
		const std::vector<Agent*>&		get_agents() const;
		const std::vector<Building*>&	get_buildings() const;

		Node*		get_node(const s3d::Vec2& position) const;

		const Camera&	get_camera() const;

		s3d::JSONValue	get_json() const;

		//Node, Path関連
		Node*		get_closest_node(const s3d::Vec2& position) const;
		Path*		get_closest_path(const s3d::Vec2& position) const;

		void	update();
	};

	extern Village* g_village;
}
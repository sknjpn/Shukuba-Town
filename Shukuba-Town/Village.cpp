#include "Village.h"

#include "Factory.h"

#include "Item.h"
#include "Node.h"
#include "Path.h"
#include "Building.h"
#include "Agent.h"
#include "Task.h"

#include "AgentVillager.h"

#include "Builder.h"
#include "BuilderBuilding.h"
#include "BuilderRoad.h"

namespace skn
{
	Village* g_village = nullptr;

	void Village::set_builder(Builder* builder)
	{
		if (m_builder != nullptr) { delete m_builder; }

		m_builder = builder;
	}

	Village::Village()
		: m_builder(nullptr)
		, m_json(U"data/data.json")
	{
		m_clock.set_time(12454.523);
		m_clock.set_speed(0.001);

		//Item�̃C���X�^���X����
		for (auto j : m_json[U"items"].arrayView())
		{
			m_items.emplace_back(Factory::make_item(j));
		}

		//�V�����G�[�W�F���g�̒ǉ�
		for (int i = 0; i < 10; i++)
		{
			m_agents.emplace_back(new AgentVillager(s3d::RandomVec2(s3d::Window::ClientRect())));
		}
	}

	Node* Village::add_node(Node* node)
	{
		m_nodes.emplace_back(node);

		return node;
	}

	Path* Village::add_path(Path* path)
	{
		m_paths.emplace_back(path);

		return path;
	}

	Agent* Village::add_agent(Agent* agent)
	{
		m_agents.emplace_back(agent);

		return agent;
	}

	Building* Village::add_building(Building* building)
	{
		m_buildings.emplace_back(building);

		return building;
	}

	Item* Village::get_item(const s3d::String& name)
	{
		return *std::find_if(m_items.begin(), m_items.end(), [&name](Item* i) { return i->get_name() == name; });
	}

	void Village::delete_node(Node* node)
	{
		auto it = std::find(m_nodes.begin(), m_nodes.end(), node);

		m_nodes.erase(it);
	}

	void Village::delete_path(Path* path)
	{
		auto it = std::find(m_paths.begin(), m_paths.end(), path);

		m_paths.erase(it);
	}

	void Village::delete_agent(Agent* agent)
	{
		auto it = std::find(m_agents.begin(), m_agents.end(), agent);

		m_agents.erase(it);
	}

	void Village::delete_building(Building* building)
	{
		auto it = std::find(m_buildings.begin(), m_buildings.end(), building);

		m_buildings.erase(it);
	}

	void Village::remove_transform(Transform * transform)
	{
		auto it = std::find(m_transforms.begin(), m_transforms.end(), transform);

		m_transforms.erase(it);
	}

	const std::vector<Item*>& Village::get_items() const
	{
		return m_items;
	}

	const std::vector<Node*>& Village::get_nodes() const
	{
		return m_nodes;
	}

	const std::vector<Path*>& Village::get_paths() const
	{
		return m_paths;
	}

	const std::vector<Agent*>& Village::get_agents() const
	{
		return m_agents;
	}

	const std::vector<Building*>& Village::get_buildings() const
	{
		return m_buildings;
	}

	Node * Village::get_node(const s3d::Vec2 & position) const
	{
		auto it = std::find_if(
			m_nodes.begin(),
			m_nodes.end(),
			[&position](Node* n) { return n->get_position() == position; }
		);

		return (it == m_nodes.end()) ? nullptr : *it;
	}

	const Camera& Village::get_camera() const
	{
		return m_camera;
	}

	s3d::JSONValue Village::get_json() const
	{
		return m_json;
	}

	Node* Village::get_closest_node(const s3d::Vec2& position) const
	{
		auto it = std::min_element(
			m_nodes.begin(),
			m_nodes.end(),
			[&position](Node* a, Node* b) { return a->get_distance_from(position) < b->get_distance_from(position); }
		);

		return (it == m_nodes.end()) ? nullptr : *it;
	}

	Path* Village::get_closest_path(const s3d::Vec2& position) const
	{
		auto it = std::min_element(
			m_paths.begin(),
			m_paths.end(),
			[&position](Path* a, Path* b) { return a->get_distance_from(position) < b->get_distance_from(position); }
		);

		return (it == m_paths.end()) ? nullptr : *it;
	}

	void Village::update()
	{
		m_clock.update();
		s3d::Print << m_clock.get_time_as_string();

		m_camera.update();

		for (auto* a : m_agents)
		{
			a->add_power(m_clock.get_speed());
			a->update();
		}

		{
			//Transformer2D
			auto t = m_camera.create_transformer();

			for (auto* p : m_paths) { p->draw(); }

			for (auto* b : m_buildings) { b->draw(); }

			for (auto* n : m_nodes)
			{
				s3d::Circle(n->get_position(), n->get_radius())
					.draw(s3d::ColorF(s3d::HSV(n->get_paths().size() * 60.0), 0.5))
					.drawFrame(2.0, s3d::Palette::Black);
			}

			for (auto* a : m_agents) { a->draw(); }
		}

		if (s3d::Key2.down()) { set_builder(new BuilderBuilding()); }
		if (s3d::Key3.down()) { set_builder(new BuilderRoad()); }

		if (m_builder != nullptr) { m_builder->update(); }
	}
}
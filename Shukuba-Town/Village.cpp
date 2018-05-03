#include "Village.h"

#include "Factory.h"

#include "Item.h"
#include "Road.h"
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

		//Itemのインスタンス生成
		for (auto j : m_json[U"items"].arrayView())
		{
			m_items.emplace_back(Factory::make_item(j));
		}

		//新しいエージェントの追加
		for (int i = 0; i < 10; i++)
		{
			m_agents.emplace_back(new AgentVillager(s3d::RandomVec2(s3d::Window::ClientRect())));
		}
	}

	Item* Village::get_item(const s3d::String& name)
	{
		return *std::find_if(m_items.begin(), m_items.end(), [&name](Item* i) { return i->get_name() == name; });
	}

	Node* Village::get_node(const s3d::Vec2 & position) const
	{
		auto it = std::find_if(
			m_nodes.begin(),
			m_nodes.end(),
			[&position](Node* n) { return n->get_position() == position; }
		);

		return (it == m_nodes.end()) ? nullptr : *it;
	}

	Node* Village::get_closest_node(const s3d::Vec2& position) const
	{
		auto it = std::min_element(
			m_nodes.begin(),
			m_nodes.end(),
			[&position](Node* a, Node* b) { return a->get_position().distanceFrom(position) < b->get_position().distanceFrom(position); }
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
					.drawFrame(2.0, s3d::Palette::Black);
			}

			for (auto* a : m_agents) { a->draw(); }
		}

		if (s3d::Key2.down()) { set_builder(new BuilderBuilding()); }
		if (s3d::Key3.down()) { set_builder(new BuilderRoad()); }

		if (m_builder != nullptr) { m_builder->update(); }
	}
}
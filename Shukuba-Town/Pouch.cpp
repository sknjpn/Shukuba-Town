#include "Pouch.h"
#include "Item.h"

namespace skn
{
	Pouch::Pouch(Item* item, int size)
		: m_item(item)
		, m_size(size)
	{

	}

	Item* Pouch::get_item() const
	{
		return m_item;
	}

	int Pouch::get_size() const
	{
		return m_size;
	}

	int Pouch::get_weight() const
	{
		return m_item->get_weight() * m_size;
	}

	void Pouch::add_item(int size)
	{
		m_size += size;
	}

	void Pouch::pull_item(int size)
	{
		m_size -= size;
	}
}
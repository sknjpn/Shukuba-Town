#include "Agent.h"
#include "Task.h"

namespace skn
{
	bool Agent::move(const s3d::Vec2& target)
	{
		double distance = get_position().distanceFrom(target);
		double speed = 1024;

		if (speed <= 0)
		{
			m_power = 0;

			return false;
		}
		else if (distance > speed * m_power)
		{
			set_position(get_position() + (target - get_position()).setLength(speed * m_power));
			m_power = 0;

			return false;
		}
		else
		{
			m_power -= distance / speed;
			set_position(target);

			return true;
		}
	}

	bool Agent::wait(double time)
	{
		if (time > m_power)
		{
			m_power = 0;

			return false;
		}
		else if (time <= 0)
		{
			return true;
		}
		else
		{
			m_power -= time;

			return true;
		}
	}

	void Agent::draw() const
	{
		s3d::Circle(get_position(), 8)
			.draw()
			.drawFrame(2.0, s3d::Palette::Black);
	}

	void Agent::update()
	{
		while (m_power > 0)
		{
			if (m_tasks.empty())
			{
				behave();
			}
			else
			{
				if (m_tasks.front()->update(this))
				{
					delete m_tasks.front();

					m_tasks.erase(m_tasks.begin());
				}
			}
		}
	}
}
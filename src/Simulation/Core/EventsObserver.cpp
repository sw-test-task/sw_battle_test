#include "EventsObserver.hpp"

#include "Unit.hpp"

#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>

namespace sw
{
	void EventsObserver::onMapCreated(uint32_t width, uint32_t height)
	{
		_eventLog.log(_tick, io::MapCreated{width, height});
	}

	void EventsObserver::onUnitSpawned(const Unit& unit, const Point& position)
	{
		_eventLog.log(_tick, io::UnitSpawned{unit.id(), unit.type(), position.x, position.y});
	}

	void EventsObserver::onUnitMarchStarted(const Unit& unit, const Point& source)
	{
		_eventLog.log(_tick, io::MarchStarted{unit.id(), source.x, source.y, unit.target().x, unit.target().y});
	}

	void EventsObserver::onUnitMarchEnded(const Unit& unit)
	{
		_eventLog.log(_tick, io::MarchEnded{unit.id(), unit.target().x, unit.target().y});
	}

	void EventsObserver::onUnitAttacked(const Unit& attacker, const Unit& target, uint32_t damage)
	{
		// Strictly speaking HP is not a mandatory trait, ho here we should check if it exists
		const auto targetHp = target.traits().getOrDefault<HP>();
		_eventLog.log(_tick, io::UnitAttacked{attacker.id(), target.id(), damage, targetHp});
	}

	void EventsObserver::onUnitDied(const Unit& unit)
	{
		_eventLog.log(_tick, io::UnitDied{unit.id()});
	}

	void EventsObserver::onUnitMoved(const Unit& unit, const Point& position)
	{
		_eventLog.log(_tick, io::UnitMoved{unit.id(), position.x, position.y});
	}

	void EventsObserver::onTick()
	{
		++_tick;
	}
}

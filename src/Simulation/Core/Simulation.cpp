#include "Simulation.hpp"

#include "SimulationContext.hpp"
#include "Unit.hpp"

#include <IO/Events/MapCreated.hpp>
#include <IO/System/EventLog.hpp>

namespace sw
{
	void Simulation::addUnit(std::unique_ptr<Unit> unit, const Point& position)
	{
		const auto id = unit->id();
		const auto type = unit->type();

		unit->setObserver(_log);
		_map->placeUnit(unit.get(), position);
		_units.push_back(std::move(unit));
		_indexById[id] = _units.size() - 1;

		_log.onUnitSpawned(*_units.back(), position);
	}

	Unit& Simulation::getUnit(uint32_t id)
	{
		const auto it = _indexById.find(id);

		if (it == _indexById.end())
		{
			throw std::logic_error("Unit was not found");
		}

		return *_units[it->second];
	}

	void Simulation::createMap(uint32_t width, uint32_t height)
	{
		if (_map.has_value())
		{
			throw std::logic_error("Map is already created");
		}

		_map.emplace(width, height, std::bind_front(&Simulation::onUnitMoved, this));
		_log.onMapCreated(width, height);
	}

	Map& Simulation::map()
	{
		if (!_map.has_value())
		{
			throw std::logic_error("Map is not created yet");
		}

		return *_map;
	}

	void Simulation::run()
	{
		_log.onTick();

		while (runOneIteration())
		{
			_log.onTick();
		}
	}

	bool Simulation::runOneIteration()
	{
		std::size_t actions = 0;
		SimulationContext ctx{map()};

		// Right now it's safe to loop over the vector because it's not possible to
		// spawn/destroy a unit out of the loop. It can be fixed locally in this
		// module if necessary.
		for (auto it = _units.begin(); it != _units.end();)
		{
			auto& unit = **it;
			if (!unit.isAlive())
			{
				it = removeDiedUnit(it);
				continue;
			}

			const auto status = unit.takeTurn(ctx);

			if (status != TurnStatus::Skipped)
			{
				++actions;
			}

			if (unit.isAlive() && unit.shouldDie())
			{
				unit.die();
			}

			++it;
		}

		// End of sumilation:
		// - there is no units acted last time OR
		// - only one unit left
		return actions > 0 && _units.size() > 1;
	}

	Simulation::Iterator Simulation::removeDiedUnit(Iterator it)
	{
		auto unitId = (it->get())->id();
		map().removeUnit(unitId);
		return _units.erase(it);
	}

	void Simulation::onUnitMoved(const Unit& unit, const Point& pos)
	{
		_log.onUnitMoved(unit, pos);

		if (unit.target() == pos)
		{
			_log.onUnitMarchEnded(unit);
		}
	}
}

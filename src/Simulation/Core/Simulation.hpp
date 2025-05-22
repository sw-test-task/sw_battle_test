#pragma once

#include "EventsObserver.hpp"
#include "Map.hpp"

#include <memory>
#include <optional>

namespace sw
{
	class Unit;

	/**
	 * Tha main class for the simulation that owns map and all units
	 */
	class Simulation
	{
	public:
		void addUnit(std::unique_ptr<Unit> unit, const Point& position);
		Unit& getUnit(uint32_t id);

		void createMap(uint32_t width, uint32_t height);
		Map& map();

		void run();

	private:
		using UnitsList = std::vector<std::unique_ptr<Unit>>;
		using Iterator = typename UnitsList::iterator;

		bool runOneIteration();
		Iterator removeDiedUnit(Iterator it);
		void onUnitMoved(const Unit& unit, const Point& pos);

		std::optional<Map> _map;
		std::unordered_map<uint32_t, std::size_t> _indexById;
		UnitsList _units;
		EventsObserver _log;
	};
}

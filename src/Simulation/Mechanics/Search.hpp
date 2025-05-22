#pragma once

#include "Simulation/Core/Map.hpp"
#include "Simulation/Core/Unit.hpp"

namespace sw
{
	/**
	 * Mechanics for search on the map
	 */

	Unit* findTargetToAttack(const Attack& attack, const Map& map);
	bool noNeighborsAround(const Unit& unit, const Map& map);
}

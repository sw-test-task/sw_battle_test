#pragma once

#include "Simulation/Core/Map.hpp"
#include "Simulation/Core/Unit.hpp"

namespace sw
{
	/**
	 * Move-specific mechanics
	 */

	TurnStatus tryMoveToTarget(const Unit& unit, Map& map);
}

#pragma once

#include "Map.hpp"

namespace sw
{
	/**
	 * Passed to units during simulation process.
	 * The goal is to control what dependencies are passed to units to avoid big coupling.
	 * It might be replaced with an abstract interface if necessary.
	 */
	struct SimulationContext
	{
		Map& map;
	};
}

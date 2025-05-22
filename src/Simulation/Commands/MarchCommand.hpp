#pragma once

#include "Simulation/Core/Simulation.hpp"
#include "Simulation/Core/Unit.hpp"

#include <IO/Commands/March.hpp>

namespace sw
{
	class MarchCommand
	{
	public:
		using IoType = io::March;

		void execute(Simulation& simulation, const io::March& command)
		{
			Point target{command.targetX, command.targetY};
			Point source{simulation.map().unitPosition(command.unitId)};
			simulation.getUnit(command.unitId).march(source, target);
		}
	};
}

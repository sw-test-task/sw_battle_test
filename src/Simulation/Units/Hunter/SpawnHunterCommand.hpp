#pragma once

#include "Hunter.hpp"
#include "Simulation/Core/Simulation.hpp"

#include <IO/Commands/SpawnHunter.hpp>

namespace sw
{
	class SpawnHunterCommand
	{
	public:
		using IoType = io::SpawnHunter;

		void execute(Simulation& simulation, const io::SpawnHunter& cmd)
		{
			auto hunter = std::make_unique<Hunter>(cmd.unitId, cmd.hp, cmd.strength, cmd.agility, cmd.range);
			simulation.addUnit(std::move(hunter), Point{cmd.x, cmd.y});
		}
	};
}

#pragma once

#include "Simulation/Core/Simulation.hpp"
#include "Swordsman.hpp"

#include <IO/Commands/SpawnSwordsman.hpp>

namespace sw
{
	class SpawnSwordsmanCommand
	{
	public:
		using IoType = io::SpawnSwordsman;

		void execute(Simulation& simulation, const io::SpawnSwordsman& cmd)
		{
			auto swordsman = std::make_unique<Swordsman>(cmd.unitId, cmd.hp, cmd.strength);
			simulation.addUnit(std::move(swordsman), Point{cmd.x, cmd.y});
		}
	};
}

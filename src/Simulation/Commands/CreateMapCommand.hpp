#pragma once

#include "Simulation/Core/Simulation.hpp"

#include <IO/Commands/CreateMap.hpp>

namespace sw
{
	class CreateMapCommand
	{
	public:
		using IoType = io::CreateMap;

		void execute(Simulation& simulation, const io::CreateMap& command)
		{
			simulation.createMap(command.width, command.height);
		}
	};
}

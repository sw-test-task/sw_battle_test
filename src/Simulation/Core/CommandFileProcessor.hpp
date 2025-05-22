#pragma once

#include "IO/System/CommandParser.hpp"
#include "Simulation/Core/Simulation.hpp"

namespace sw
{
	class CommandFileProcessor
	{
	public:
		explicit CommandFileProcessor(Simulation& simulation) :
				_simulation(simulation)
		{}

		template <class TCommand, class... Args>
		void registerCommand(Args&&... args)
		{
			using IoType = typename TCommand::IoType;
			_parser.add<IoType>(
				[this, ... args = std::forward<Args>(args)](const IoType& command)
				{
					TCommand executor(std::forward<Args>(args)...);
					executor.execute(_simulation, command);
				});
		}

		void processFile(std::istream& stream)
		{
			_parser.parse(stream);
		}

	private:
		Simulation& _simulation;
		io::CommandParser _parser;
	};
}

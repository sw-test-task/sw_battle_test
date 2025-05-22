#include "Simulation/Commands/CreateMapCommand.hpp"
#include "Simulation/Commands/MarchCommand.hpp"
#include "Simulation/Core/CommandFileProcessor.hpp"
#include "Simulation/Core/Simulation.hpp"
#include "Simulation/Units/Hunter/SpawnHunterCommand.hpp"
#include "Simulation/Units/Swordman/SpawnSwordsmanCommand.hpp"

#include <cstring>
#include <fstream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	Simulation simulation;
	CommandFileProcessor commandProcessor(simulation);

	commandProcessor.registerCommand<CreateMapCommand>();
	commandProcessor.registerCommand<SpawnSwordsmanCommand>();
	commandProcessor.registerCommand<SpawnHunterCommand>();
	commandProcessor.registerCommand<MarchCommand>();

	if (std::strcmp(argv[1], "-") == 0)
	{
		commandProcessor.processFile(std::cin);
	}
	else
	{
		std::ifstream file(argv[1]);
		if (!file)
		{
			throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
		}
		commandProcessor.processFile(file);
	}

	simulation.run();
	return 0;
}

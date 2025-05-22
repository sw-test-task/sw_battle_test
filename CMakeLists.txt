cmake_minimum_required(VERSION 3.27)

project(sw_battle_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Existing sources
file(GLOB_RECURSE IO_SOURCES src/IO/*.cpp src/IO/*.hpp)

add_executable(sw_battle_test
    ${IO_SOURCES}
    src/main.cpp

    src/Simulation/Core/Attack.hpp
    src/Simulation/Core/CommandFileProcessor.hpp
    src/Simulation/Core/EventsObserver.cpp
    src/Simulation/Core/EventsObserver.hpp
    src/Simulation/Core/Map.cpp
    src/Simulation/Core/Map.hpp
    src/Simulation/Core/TraitList.hpp
    src/Simulation/Core/Simulation.cpp
    src/Simulation/Core/Simulation.hpp
    src/Simulation/Core/SimulationContext.hpp
    src/Simulation/Core/Point.hpp
    src/Simulation/Core/TurnStatus.hpp
    src/Simulation/Core/Unit.hpp

    src/Simulation/Mechanics/Move.hpp
    src/Simulation/Mechanics/Move.cpp
    src/Simulation/Mechanics/Search.hpp
    src/Simulation/Mechanics/Search.cpp

    src/Simulation/Commands/CreateMapCommand.hpp
    src/Simulation/Commands/MarchCommand.hpp

    src/Simulation/Traits/Agility.hpp
    src/Simulation/Traits/AttackRange.hpp
    src/Simulation/Traits/HP.hpp
    src/Simulation/Traits/MoveRange.hpp
    src/Simulation/Traits/OccupyTile.hpp
    src/Simulation/Traits/Strength.hpp
    src/Simulation/Traits/TrivialTrait.hpp

    src/Simulation/Units/Swordman/Swordsman.hpp
    src/Simulation/Units/Swordman/SpawnSwordsmanCommand.hpp

    src/Simulation/Units/Hunter/Hunter.hpp
    src/Simulation/Units/Hunter/SpawnHunterCommand.hpp
)

include_directories(sw_battle_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GNUInstallDirs)
install(TARGETS sw_battle_test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

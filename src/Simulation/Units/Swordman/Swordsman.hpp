#pragma once

#include "Simulation/Core/Unit.hpp"
#include "Simulation/Mechanics/Move.hpp"
#include "Simulation/Mechanics/Search.hpp"
#include "Simulation/Traits/OccupyTile.hpp"
#include "Simulation/Traits/Strength.hpp"

namespace sw
{
	class Swordsman : public Unit
	{
	public:
		static constexpr auto ID = "Swordsman";

		explicit Swordsman(uint32_t id, uint32_t hp, uint32_t strength) :
				Unit(id, ID)
		{
			traits().set<HP>(hp);
			traits().set<Strength>(strength);
			traits().set<OccupyTile>(true);
		}

		TurnStatus takeTurn(SimulationContext& ctx) override
		{
			Attack attack{.attacker = this, .type = AttackType::Melee};

			if (auto* target = findTargetToAttack(attack, ctx.map))
			{
				target->takeDamage(*this, traits().get<Strength>());
				return TurnStatus::Acted;
			}

			return tryMoveToTarget(*this, ctx.map);
		}
	};
}

#pragma once

#include "Simulation/Core/Unit.hpp"
#include "Simulation/Mechanics/Move.hpp"
#include "Simulation/Mechanics/Search.hpp"
#include "Simulation/Traits/Agility.hpp"
#include "Simulation/Traits/AttackRange.hpp"
#include "Simulation/Traits/OccupyTile.hpp"
#include "Simulation/Traits/Strength.hpp"

namespace sw
{
	class Hunter : public Unit
	{
	public:
		static constexpr auto ID = "Hunter";

		explicit Hunter(uint32_t id, uint32_t hp, uint32_t strength, uint32_t agility, uint32_t range) :
				Unit(id, ID)
		{
			traits().set<HP>(hp);
			traits().set<Strength>(strength);
			traits().set<Agility>(agility);
			traits().set<AttackRange>(range);
			traits().set<OccupyTile>(true);
		}

		TurnStatus takeTurn(SimulationContext& ctx) override
		{
			if (noNeighborsAround(*this, ctx.map))
			{
				// Ranged attack
				Attack attack{
					.attacker = this,
					.type = AttackType::Ranged,
					.range = traits().get<AttackRange>(),
				};

				if (auto* target = findTargetToAttack(attack, ctx.map))
				{
					target->takeDamage(*this, traits().get<Agility>());
					return TurnStatus::Acted;
				}
			}

			// Melee attack
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

#include "Move.hpp"

#include "Simulation/Traits/MoveRange.hpp"

namespace sw
{
	bool makeOneMovement(const Unit& unit, Map& map)
	{
		const auto from = map.unitPosition(unit.id());
		const auto to = unit.target();

		if (from == to)
		{
			return false;
		}

		// The simplest logic to avoid over-complication
		int dx = (to.x > from.x) ? 1 : (to.x < from.x) ? -1 : 0;
		int dy = (to.y > from.y) ? 1 : (to.y < from.y) ? -1 : 0;

		Point newPosition = from;

		if (!newPosition.shift(dx, dy) || !map.canPlaceUnitAt(unit, newPosition))
		{
			return false;
		}

		map.moveUnit(unit.id(), newPosition);
		return true;
	}

	TurnStatus tryMoveToTarget(const Unit& unit, Map& map)
	{
		uint32_t steps = unit.traits().getOrDefault<MoveRange>(1);
		uint32_t stepsMade = 0;

		while (steps > 0)
		{
			if (!makeOneMovement(unit, map))
			{
				break;
			}

			--steps;
			++stepsMade;
		}

		return stepsMade > 0 ? TurnStatus::Moved : TurnStatus::Skipped;
	}
}

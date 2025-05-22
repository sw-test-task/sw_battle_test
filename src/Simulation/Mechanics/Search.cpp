#include "Search.hpp"

namespace sw
{
	template <class TVisitor>
	Unit* visitEachPointInRadius(const Point& center, const Map& map, uint32_t radius, const TVisitor& visitor)
	{
		const int signedRadius = static_cast<int>(radius);

		for (int dy = -signedRadius; dy <= signedRadius; ++dy)
		{
			for (int dx = -signedRadius; dx <= signedRadius; ++dx)
			{
				if (dx == 0 && dy == 0)
				{
					continue;
				}

				Point p = center;

				if (p.shift(dx, dy) && map.inBounds(p))
				{
					if (auto unit = visitor(p))
					{
						return unit;
					}
				}
			}
		}

		return nullptr;
	}

	template <class TPredicate>
	Unit* findNeighbor(const Point& center, const Map& map, uint32_t radius, const TPredicate& predicate)
	{
		const auto visitor = [&](const Point& p) -> Unit*
		{
			for (auto* unit : map.unitsAt(p))
			{
				if (predicate(*unit))
				{
					return unit;
				}
			}

			return nullptr;
		};

		return visitEachPointInRadius(center, map, radius, visitor);
	}

	Unit* findTargetToAttack(const Attack& attack, const Map& map)
	{
		const auto predicate = [&](const Unit& unit)
		{
			return unit.canBeAttackedBy(attack);
		};

		return findNeighbor(map.unitPosition(attack.attacker->id()), map, attack.range, predicate);
	}

	bool noNeighborsAround(const Unit& unit, const Map& map)
	{
		const int radius = 1;
		const auto predicate = [&](const Unit&)
		{
			return true;
		};

		return findNeighbor(map.unitPosition(unit.id()), map, radius, predicate) == nullptr;
	}
}

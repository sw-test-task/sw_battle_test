#pragma once

#include "Point.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

namespace sw
{
	class Unit;

	/**
	 * 2D map that doesn't own Units (stores pointers)
	 */
	class Map
	{
	public:
		using MoveObserver = std::function<void(const Unit&, const Point&)>;
		using UnitsList = std::vector<Unit*>;

		Map(uint32_t width, uint32_t height, const MoveObserver& moveObserver);

		void placeUnit(Unit* unit, const Point& position);
		void removeUnit(uint32_t unitId);
		void moveUnit(uint32_t unitId, const Point& newPosition);

		UnitsList unitsAt(const Point& p) const;
		Point unitPosition(uint32_t unitId) const;

		bool canPlaceUnitAt(const Unit& unit, const Point& p) const;
		bool inBounds(const Point& p) const;

	private:
		struct Cell
		{
			bool occupied = false;
			UnitsList units;
		};

		struct UnitIdInfo
		{
			Unit* unit;
			Point position;
		};

		UnitIdInfo& getByUnitId(uint32_t unitId);

		std::vector<std::vector<Cell>> _grid;
		std::unordered_map<uint32_t, UnitIdInfo> _byUnitId;
		uint32_t _width;
		uint32_t _height;
		MoveObserver _moveObserver;
	};
}

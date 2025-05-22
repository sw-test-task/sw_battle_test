#include "Map.hpp"

#include "Simulation/Traits/OccupyTile.hpp"
#include "Unit.hpp"

#include <stdexcept>

namespace sw
{
	Map::Map(uint32_t width, uint32_t height, const MoveObserver& moveObserver) :
			_grid(height, std::vector<Cell>(width)),
			_width(width),
			_height(height),
			_moveObserver(moveObserver)
	{}

	void Map::placeUnit(Unit* unit, const Point& position)
	{
		if (!inBounds(position))
		{
			throw std::logic_error("position is out of map");
		}

		auto& cell = _grid[position.y][position.x];

		if (cell.occupied && unit->traits().getOrDefault<OccupyTile>())
		{
			throw std::logic_error("position is already occupied");
		}

		cell.units.push_back(unit);
		_byUnitId[unit->id()] = {unit, position};
	}

	void Map::removeUnit(uint32_t unitId)
	{
		const auto [unit, pos] = getByUnitId(unitId);
		bool occupied = unit->traits().getOrDefault<OccupyTile>();

		auto& cell = _grid[pos.y][pos.x];
		std::erase_if(cell.units, [&](const auto* u) { return u->id() == unitId; });

		if (occupied)
		{
			cell.occupied = false;
		}

		_byUnitId.erase(unitId);
	}

	Map::UnitsList Map::unitsAt(const Point& p) const
	{
		if (inBounds(p))
		{
			return _grid[p.y][p.x].units;
		}

		return {};
	}

	Point Map::unitPosition(uint32_t unitId) const
	{
		const auto it = _byUnitId.find(unitId);

		if (it == _byUnitId.end())
		{
			throw std::logic_error("unit was not found on the map");
		}

		return it->second.position;
	}

	void Map::moveUnit(uint32_t unitId, const Point& newPosition)
	{
		if (!inBounds(newPosition))
		{
			throw std::logic_error("position is out of map");
		}

		auto& [unit, currentPos] = getByUnitId(unitId);

		auto& srcCell = _grid[currentPos.y][currentPos.x];
		auto& dstCell = _grid[newPosition.y][newPosition.x];

		if (dstCell.occupied && unit->traits().getOrDefault<OccupyTile>())
		{
			throw std::logic_error("position is already occupied");
		}

		std::erase_if(srcCell.units, [&](const auto* u) { return u->id() == unitId; });
		dstCell.units.push_back(unit);
		currentPos = newPosition;

		if (unit->traits().getOrDefault<OccupyTile>())
		{
			dstCell.occupied = true;
		}

		_moveObserver(*unit, newPosition);
	}

	Map::UnitIdInfo& Map::getByUnitId(uint32_t unitId)
	{
		const auto it = _byUnitId.find(unitId);

		if (it == _byUnitId.end())
		{
			throw std::logic_error("unit was not found on the map");
		}

		return it->second;
	}

	bool Map::canPlaceUnitAt(const Unit& unit, const Point& p) const
	{
		if (!inBounds(p))
		{
			return false;
		}

		const auto& cell = _grid[p.y][p.x];
		return !cell.occupied || !unit.traits().getOrDefault<OccupyTile>();
	}

	bool Map::inBounds(const Point& p) const
	{
		return p.x < _width && p.y < _height;
	}
}

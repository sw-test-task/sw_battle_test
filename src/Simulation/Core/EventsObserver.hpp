#pragma once

#include "Simulation/Core/Point.hpp"

#include <IO/System/EventLog.hpp>

namespace sw
{
	class Unit;

	/**
	 * A wrapper around EventLog with encapsulated 'tick'.
	 * Ideally it should be an abstract interface.
	 */
	class EventsObserver
	{
	public:
		void onMapCreated(uint32_t width, uint32_t height);
		void onUnitSpawned(const Unit& unit, const Point& position);
		void onUnitMarchStarted(const Unit& unit, const Point& source);
		void onUnitMarchEnded(const Unit& unit);
		void onUnitAttacked(const Unit& attacker, const Unit& target, uint32_t damage);
		void onUnitDied(const Unit& unit);
		void onUnitMoved(const Unit& unit, const Point& position);
		void onTick();

	private:
		EventLog _eventLog;
		uint64_t _tick = 1;
	};
}

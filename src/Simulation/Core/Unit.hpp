#pragma once

#include "Attack.hpp"
#include "Point.hpp"
#include "Simulation/Core/EventsObserver.hpp"
#include "Simulation/Traits/HP.hpp"
#include "SimulationContext.hpp"
#include "TraitList.hpp"
#include "TurnStatus.hpp"

#include <cstdint>
#include <string>

namespace sw
{
	/**
	 * Base abstract class for Units with customization points
	 */
	class Unit
	{
	public:
		Unit(uint32_t id, const std::string& type) :
				_id(id),
				_type(type)
		{}

		uint32_t id() const
		{
			return _id;
		}

		std::string type() const
		{
			return _type;
		}

		Point target() const
		{
			return _target;
		}

		TraitList& traits()
		{
			return _traits;
		}

		const TraitList& traits() const
		{
			return _traits;
		}

		void die()
		{
			if (!_died)
			{
				_died = true;
				_observer->onUnitDied(*this);
			}
		}

		bool isAlive() const
		{
			return !_died;
		}

		void setObserver(EventsObserver& observer)
		{
			_observer = &observer;
		}

		void march(const Point& source, const Point& target)
		{
			_target = target;
			_observer->onUnitMarchStarted(*this, source);
		}

		void takeDamage(const Unit& attacker, uint32_t damage)
		{
			applyDamage(attacker, damage);
			_observer->onUnitAttacked(attacker, *this, damage);

			if (shouldDie())
			{
				die();
			}
		}

		/**
		 * The main point for the Unit's logic
		 */
		virtual TurnStatus takeTurn(SimulationContext& ctx) = 0;

		/**
		 * Might be overloaded for units that cannot be attacked in some ways.
		 *
		 * Example 1:
		 * return attack.type != AttackType::Melee;
		 *
		 * Example 2:
		 * return distance(attack.attacker, this) + 1 <= attack.radius;
		 *
		 * Example 3:
		 * return false;
		 */
		virtual bool canBeAttackedBy(const Attack& /*attack*/) const
		{
			return true;
		}

		/**
		 * Apply damage as a result of an attack,
		 * Might be overloaded for units that don't have HP.
		 * Default logic - reduce HP.
		 */
		virtual uint32_t applyDamage(const Unit& /*attacker*/, uint32_t damage)
		{
			uint32_t actualDamage = 0;

			if (_traits.has<HP>())
			{
				auto& hp = _traits.get<HP>();
				actualDamage = std::min(hp, damage);
				hp -= actualDamage;
			}

			return actualDamage;
		}

		/**
		 * Check if Unit is alive by its trais.
		 * Might be overloaded for units that don't have HP.
		 * Default logic - check if HP is 0.
		 */
		virtual bool shouldDie() const
		{
			if (_traits.has<HP>())
			{
				return _traits.get<HP>() == 0;
			}

			return false;
		}

		virtual ~Unit() = default;

	private:
		uint32_t _id;
		std::string _type;
		Point _target;
		TraitList _traits;
		bool _died = false;
		EventsObserver* _observer = nullptr;
	};
}

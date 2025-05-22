#pragma once

#include <cstdint>

namespace sw
{
	class Unit;

	enum class AttackType
	{
		Melee,
		Ranged,
	};

	struct Attack
	{
		Unit* attacker;
		AttackType type;
		uint32_t range = 1;
	};
}

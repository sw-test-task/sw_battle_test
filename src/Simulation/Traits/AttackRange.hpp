#pragma once

#include "TrivialTrait.hpp"

#include <cstdint>

namespace sw
{
	struct AttackRange : public TrivialTrait<uint32_t>
	{};
}

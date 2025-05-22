#pragma once

#include "TrivialTrait.hpp"

#include <cstdint>

namespace sw
{
	struct Agility : public TrivialTrait<uint32_t>
	{};
}

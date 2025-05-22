#pragma once

#include "TrivialTrait.hpp"

#include <cstdint>

namespace sw
{
	struct Strength : public TrivialTrait<uint32_t>
	{};
}

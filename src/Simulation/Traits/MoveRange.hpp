#pragma once

#include "TrivialTrait.hpp"

#include <cstdint>

namespace sw
{
	struct MoveRange : public TrivialTrait<uint32_t>
	{};
}

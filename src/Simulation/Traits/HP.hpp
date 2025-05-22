#pragma once

#include "TrivialTrait.hpp"

#include <cstdint>

namespace sw
{
	struct HP : public TrivialTrait<uint32_t>
	{};
}

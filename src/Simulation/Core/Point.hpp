#pragma once

#include <cstdint>
#include <limits>

namespace sw
{
	struct Point
	{
		uint32_t x = 0;
		uint32_t y = 0;

		bool shift(int dx, int dy)
		{
			int64_t newX = x + static_cast<int64_t>(dx);
			int64_t newY = y + static_cast<int64_t>(dy);

			if (newX < 0 || newX > std::numeric_limits<uint32_t>::max())
			{
				return false;
			}

			if (newY < 0 || newY > std::numeric_limits<uint32_t>::max())
			{
				return false;
			}

			x = static_cast<uint32_t>(newX);
			y = static_cast<uint32_t>(newY);
			return true;
		}

		bool operator==(const Point&) const noexcept = default;
	};
}

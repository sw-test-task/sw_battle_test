#pragma once

namespace sw
{
	/**
	 * Helper to reduce boilerplate for traits that have only one single int/bool.
	 */
	template <class T>
	struct TrivialTrait
	{
		static constexpr bool IsTrivial = true;
		using type = T;

		T value{};
	};
}

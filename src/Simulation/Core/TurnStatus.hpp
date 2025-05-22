#pragma once

namespace sw
{
	/**
	 * Turn status that unit returns after each turn
	 */
	enum class TurnStatus
	{
		/// No action was made because the unit is blocked and cannot do anything
		Skipped,

		/// An action made
		Acted,

		/// No action made, just a movement
		Moved,

		/// Extension point: Died, Slept, etc.
	};
}

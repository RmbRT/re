#ifndef __re_timer_hpp_defined
#define __re_timer_hpp_defined

#include "types.hpp"
#include "defines.hpp"

namespace re
{
	/** Represents a continuous timer that counts the time since it was created, in seconds. */
	class ContinuousTimer
	{
	protected:
		double _time_0; // the time this timer was created at.
		double _time_previous; // the previous last time this time was updated.
		double _time; // last time this timer was updated.
		double _delta; // stores the delta time between the updates.
	public:
		ContinuousTimer();

		/** Returns the time in seconds that passed between the last two update calls. */
		REIL double delta() const;

		/** Returns the time in seconds that passed since the timer was created. */
		REIL double age() const;

		void update();
	};
}

#include "Timer.inl"

#endif
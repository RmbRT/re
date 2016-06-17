#ifndef __re_timer_inl_defined
#define __re_timer_inl_defined
#ifndef __re_timer_hpp_defined
#error "re/timer.hpp expected"
#else
namespace re
{
	REIL double ContinuousTimer::delta() const
	{
		return _delta;
	}

	REIL double ContinuousTimer::age() const
	{
		return _time-_time_0;
	}
}
#endif
#endif
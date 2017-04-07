#include "Timer.hpp"
#include "graphics/gl/OpenGL.hpp"

namespace re
{
	ContinuousTimer::ContinuousTimer() : _time_0(glfwGetTime()), _time_previous(_time_0), _time(_time_0), _delta(0.0) { }
	void ContinuousTimer::update()
	{
		_time_previous = _time;
		_time = glfwGetTime();
		_delta = _time-_time_previous;
	}
}
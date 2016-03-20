#ifndef __re_re_hpp_defined
#define __re_re_hpp_defined
/** This is the root namespace of the RmbRT engine. */
namespace re
{
	/** Contains functions for loading data from files. */
	namespace file		{	}
	/** Contains classes and functions for mathematical calculations. */
	namespace math		{	}
	/** Contains classes and functions for rendering or window management. */
	namespace graphics	{	}
	/** Contains classes for object communication. */
	namespace messaging	{	}
	/** Contains classes for handling input by the user. */
	namespace input		{	}
}

#include "defines.hpp"
#include "types.hpp"
#include "LogFile.hpp"
#include "math/Math.hpp"
#include "graphics/Graphics.hpp"
#include "input/Input.hpp"
#include "messaging/Emitter.hpp"


#endif
#ifndef __re_re_hpp_defined
#define __re_re_hpp_defined
/*This is the root namespace of the RmbRT engine.*/
namespace re
{
	/*Contains classes and functions for mathematical calculations.*/
	namespace math		{	}
	/*Contains classes and functions for rendering or window management.*/
	namespace graphics	{	}
	/*Contains classes for object communication.*/
	namespace messaging	{	}
	/*Contains classes for handling input by the user.*/
	namespace input		{	}
	/*Contains singleton classes that contain internal logic and provide interfaces for controlling the flow of the program.*/
	namespace modules	{	}
}

#include "defines.hpp"
#include "types.hpp"
#include "LogFile.hpp"
#include "math\Math.hpp"
#include "graphics\Graphics.hpp"
#include "modules\Modules.hpp"
#include "input\Input.hpp"
#include "messaging\Emitter.hpp"


#endif
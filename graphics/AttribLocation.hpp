#ifndef __re_attriblocation_hpp_defined
#define __re_attriblocation_hpp_defined

#include "../types.hpp"

namespace re
{
	namespace graphics
	{
		/*This specifies the usage of a GLBuffer.*/
		RE_ENUM(AttribLocation)
		{
			AL_POSITION,
			AL_NORMAL,
			AL_COLOR,
			AL_TEXCOORD
		};

		const string AttributeNames[] = { "RE_POSITION", "RE_NORMAL", "RE_COLOR", "RE_TEXCOORD" };

	}
}
#endif
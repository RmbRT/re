#ifndef __re_videomode_hpp_defined
#define __re_videomode_hpp_defined

namespace re
{
	namespace graphics
	{
		struct VideoMode
		{
			int width;
			int height;
			int bitsR, bitsG, bitsB;
			int frequency;
		};
	}
}

#endif
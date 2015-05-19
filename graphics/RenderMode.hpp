#ifndef __re_rendermode_hpp_defined
#define __re_rendermode_hpp_defined

namespace re
{
	namespace graphics
	{
		/*Contains rendering modes for drawing models.*/
		RE_ENUM(RenderMode)
		{
			RM_LINE_STRIP,
			RM_LINES,
			RM_TRIANGLES,
			RM_TRIANGLE_STRIP,
			RM_POINTS,
			RM_QUADS,
			RM_QUAD_STRIP,
			RM_TRIANGLE_FAN
		};
	}
}

#endif
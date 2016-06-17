#ifndef __re_graphics_gl_version_hpp_defined
#define __re_graphics_gl_version_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"


namespace re
{
	namespace graphics
	{
		namespace gl
		{
			class Version
			{
				uint m_major;
				uint m_minor;

			public:
				RECX Version(uint major, uint minor);

				RECX uint major() const;
				RECX uint minor() const;

				RECX bool operator<(Version const& rhs) const;
				RECX bool operator>=(Version const& rhs) const;

				RECX bool valid() const;
			};
		}
	}
}



#endif
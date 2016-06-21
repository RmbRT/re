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
				uint_t m_major;
				uint_t m_minor;

			public:
				RECX Version(uint_t major, uint_t minor);

				RECX uint_t major() const;
				RECX uint_t minor() const;

				RECX bool operator<(Version const& rhs) const;
				RECX bool operator>=(Version const& rhs) const;

				RECX bool valid() const;
			};
		}
	}
}



#endif
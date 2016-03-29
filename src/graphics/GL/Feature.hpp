#ifndef __re_graphics_gl_feature_hpp_defined
#define __re_graphics_gl_feature_hpp_defined

namespace re
{
	namespace graphics
	{
		namespace GL
		{

			template<class Ctx>
			typedef void (Ctx::*feature_fn_t)();

			/** Features that depend on a minimal Context Version. */
			template<class Ctx>
			class Feature
			{
				/** The lowest supported Version. */
				Version m_min_version;
				/** The highest supported Version. */
				Version m_max_version;
				/** The function to be called for a Context with a supported Version. */
				feature_fn_t m_function;
			public:
				RECX Feature(feature_fn_t function);
				/** Creates a Feature that targets all Versions >= the given version. */
				RECX Feature(Version min_version, feature_fn_t function);
				RECX Feature(Version min_version, Version max_version, feature_fn_t function);

				/** Calls the function with the given Context as argument, if max_version >= Context Version >= min_version.
					If max_version is invalid, then it is ignored.
				@param[in] context:
					The Context to be forwarded to the function in case the Context Version is targeted by this Feature.
				@return Whether the function was called. */
				RECX bool operator() (Ctx &context) const;
			};
		}
	}
}

#include "Feature.inl"

#endif
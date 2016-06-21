#ifndef __re_plane_hpp_defined
#define __re_plane_hpp_defined

#include "Vector.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		/** Represents a plane consisting of a position and the normal vector of the plane. */
		struct NormalPlane
		{
			NormalPlane(const vec3<T> &position, const vec3<T> &normal): position(position), normal(normal) { }
			NormalPlane(const vec3<T> &position, const vec3<T> &u, const vec3<T> &v) : position(position), normal(cross(u,v)) { }

			bool contains(const vec3<T> &x) { return dot(x-position, normal) == 0; }

			vec3<T> position;
			vec3<T> normal;
		};

		template<class T>
		/** Represents a plane consisting of a position, and two axis. */
		struct STPlane
		{
			STPlane() : position(), s(), t() { }
			STPlane(const vec3<T> position, const vec3<T> &s, const vec3<T> &t): position(position), s(s), t(t) { }

			bool contains(const vec3<T> &x) { return dot(x-position, cross(s,t)) == 0; }

			vec3<T> position;
			vec3<T> s, t;
		};
	}
}

#endif
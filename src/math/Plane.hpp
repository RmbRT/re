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
			NormalPlane(
				Vec3<T> const& position,
				Vec3<T> const& normal): position(position), normal(normal) { }
			NormalPlane(
				Vec3<T> const& position,
				Vec3<T> const& u,
				Vec3<T> const& v) : position(position), normal(cross(u,v)) { }

			bool contains(
				Vec3<T> const& x) { return dot(x-position, normal) == 0; }

			Vec3<T> position;
			Vec3<T> normal;
		};

		template<class T>
		/** Represents a plane consisting of a position, and two axis. */
		struct STPlane
		{
			STPlane() : position(), s(), t() { }
			STPlane(
				Vec3<T> position,
				Vec3<T> const& s,
				Vec3<T> const& t): position(position), s(s), t(t) { }

			bool contains(
				Vec3<T> const& x) { return dot(x-position, cross(s,t)) == 0; }

			Vec3<T> position;
			Vec3<T> s, t;
		};
	}
}

#endif
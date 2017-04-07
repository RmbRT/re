#ifndef __re_vector_hpp_defined
#define __re_vector_hpp_defined

#include <math.h>
#include "../defines.hpp"
#include "../base_types.hpp"
#include <array>

namespace re
{
	namespace math
	{
		template<class T>
		struct Vec2;
		template<class T>
		struct Vec3;
		template<class T>
		struct Vec4;

		typedef Vec2<byte_t> byte2_t, bvec2_t, vec2b_t;
		typedef Vec3<byte_t> byte3_t, bvec3_t, vec3b_t;
		typedef Vec4<byte_t> byte4_t, bvec4_t, vec4b_t;
		typedef Vec2<ubyte_t> ubyte2_t, ubvec2_t, vec2ub_t;
		typedef Vec3<ubyte_t> ubyte3_t, ubvec3_t, vec3ub_t;
		typedef Vec4<ubyte_t> ubyte4_t, ubvec4_t, vec4ub_t;

		typedef Vec2<float> float2_t, fvec2_t, vec2f_t;
		typedef Vec3<float> float3_t, fvec3_t, vec3f_t;
		typedef Vec4<float> float4_t, fvec4_t, vec4f_t;

		typedef Vec2<double> double2_t, dvec2_t, vec2d_t;
		typedef Vec3<double> double3_t, dvec3_t, vec3d_t;
		typedef Vec4<double> double4_t, dvec4_t, vec4d_t;

		typedef Vec2<int> int2_t, ivec2_t, vec2i_t;
		typedef Vec3<int> int3_t, ivec3_t, vec3i_t;
		typedef Vec4<int> int4_t, ivec4_t, vec4i_t;

		typedef Vec2<short> short2_t, hvec2_t, vec2h_t;
		typedef Vec3<short> short3_t, hvec3_t, vec3h_t;
		typedef Vec4<short> short4_t, hvec4_t, vec4h_t;

		typedef Vec2<unsigned int> uivec2_t, uint2_t, vec2ui_t;
		typedef Vec3<unsigned int> uivec3_t, uint3_t, vec3ui_t;
		typedef Vec4<unsigned int> uivec4_t, uint4_t, vec4ui_t;
		typedef Vec2<unsigned short> uhvec2_t, ushort2_t, vec2uh_t;
		typedef Vec3<unsigned short> uhvec3_t, ushort3_t, vec3uh_t;
		typedef Vec4<unsigned short> uhvec4_t, ushort4_t, vec4uh_t;


		template<class T>
		/** Template 2-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct Vec2
		{
			/** Creates a zero-vector. */
			RECX Vec2();
			/** Creates a vector with the given coordinates. */
			RECX Vec2(re::util::copy_arg_t<T> x, re::util::copy_arg_t<T> y);

			RECX Vec2(Vec3<T> const& v);
			RECX Vec2(Vec4<T> const& v);

			template<class U>
			/** Converts this vector to a vector of the given type. */
			RECX explicit operator Vec2<U>() const;

			/** Converts this vector to a C-style array. */
			RECX14 operator T*();
			/** Converts this vector to a C-style array. */
			RECX operator T const*() const;

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector. */
			T y;
		};

		template<class T>
		RECX bool operator==(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		RECX bool operator!=(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		RECX Vec2<T> operator+(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		RECX Vec2<T> operator-(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		RECX Vec2<T> operator*(Vec2<T> const& a, float b);
		template<class T>
		RECX Vec2<T> operator*(Vec2<T> const& a, double b);
		template<class T>
		RECX Vec2<T> operator*(Vec2<T> const& a, int b);
		template<class T>
		RECX Vec2<T> operator*(float a, Vec2<T> const&b);
		template<class T>
		RECX Vec2<T> operator*(double a, Vec2<T> const& b);
		template<class T>
		RECX Vec2<T> operator*(int a, Vec2<T> const& b);

		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		RECX Vec2<T> operator / (Vec2<T> const& a, float b);
		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		RECX Vec2<T> operator / (Vec2<T> const& a, double b);
		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		RECX Vec2<T> operator / (Vec2<T> const& a, int b);
		template<class T>
		/** Calculates the dot product of the given vectors as a double. */
		RECX double dotd(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		/** Calculates the dot product of the given vectors as a float. */
		RECX float dotf(Vec2<T> const& a, Vec2<T> const& b);
		template<class T>
		/** Calculates the dot product of the given vectors as the element type of the vectors. */
		RECX T dot(Vec2<T> const& a, Vec2<T> const& b);

		template<class T>
		/** Calculates the length of a vector as a double. */
		REIL double abs(Vec2<T> const& v);
		template<class T>
		/** Calculates the length of a vector as a float. */
		REIL float absf(Vec2<T> const& v);
		template<class T>
		/** Divides the given vector by its length. */
		RECX Vec2<T> norm(Vec2<T> const& a);

		template<class T, size_t sz>
		Vec2<T> avg(std::array<Vec2<T>, sz> const&);


		template<class T>
		/** Template 3-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct Vec3
		{
			template<class U>
			/** Converts this vector to a vector of the given type. */
			RECX explicit operator Vec3<U>() const;

			/** Creates a vector with the given coordinates. */
			RECX Vec3(copy_arg_t<T> x, copy_arg_t<T> y, copy_arg_t<T> z);
			/** Creates a zero-vector. */
			RECX Vec3();

			RECX Vec3(Vec4<T> const& v);

			/** Converts this vector to a C-style array. */
			RECX operator const T*() const;
			/** Converts this vector to a C-style array. */
			RECX14 operator T*();

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector. */
			T y;
			/** The z (third) coordinate of the vector. */
			T z;
		};

		template<class T> bool operator==(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> bool operator!=(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> Vec3<T> operator+(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> Vec3<T> operator-(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> Vec3<T> operator*(Vec3<T> const& a, float b);
		template<class T> Vec3<T> operator*(Vec3<T> const& a, double b);
		template<class T> Vec3<T> operator*(Vec3<T> const& a, int b);
		template<class T> Vec3<T> operator*(float a, Vec3<T> const& b);
		template<class T> Vec3<T> operator*(double a, Vec3<T> const& b);
		template<class T> Vec3<T> operator*(int a, Vec3<T> const& b);
		template<class T> Vec3<T> operator / (Vec3<T> const& a, float b);
		template<class T> Vec3<T> operator / (Vec3<T> const& a, double b);
		template<class T> Vec3<T> operator / (Vec3<T> const& a, int b);
		template<class T> double dotd(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> float dotf(Vec3<T> const& a, Vec3<T> const& b);
		template<class T> T dot(Vec3<T> const& a, Vec3<T> const& b);
		/** Calculates the length of the given vector as double. */
		template<class T> double abs(Vec3<T> const& v);
		/** Calculates the length of the given vector as float. */
		template<class T> float absf(Vec3<T> const& v);
		/** Calculates the cross product of the given vectors. */
		template<class T> Vec3<T> cross(Vec3<T> const& a, Vec3<T> const& b);
		/** Divides the given vector by its length. */
		template<class T> Vec3<T> norm(Vec3<T> const& a);
		/** Calculates the square of the distance between the given vectors. */
		template<class T> T sqr_dist(Vec3<T> const& a, Vec3<T> const& b);
		/** Calculates the square of the length of the given vector. */
		template<class T> T sqr_abs(Vec3<T> const& a);

		template<class T, size_t sz>
		Vec3<T> abs(std::array<Vec3<T>, sz> const&);


		template<class T>
		/** Template 4-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct Vec4
		{
			template<class U>
			RECX explicit operator Vec4<U>() const;

			/** Creates a 4-dimensional vector with the given coordinates.
				@param[in] xyz:
					The first three coordinates of the vector.
				@param[in] w:
					The fourth coordinate of the vector. */
			RECX Vec4(Vec3<T> const& xyz, copy_arg_t<T> w);
			/** Creates a 4-dimensional vector with the given coordinates. */
			RECX Vec4(
				copy_arg_t<T> x,
				copy_arg_t<T> y,
				copy_arg_t<T> z,
				copy_arg_t<T> w);

			/** Creates a zero-vector. */
			RECX Vec4();

			/** Converts this vector to a C-style array. */
			RECX operator const T*() const;
			/** Converts this vector to a C-style array. */
			RECX14 operator T*();

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector. */
			T y;
			/** The z (third) coordinate of the vector. */
			T z;
			/** The w (fourth) coordinate of the vector. */
			T w;
		};

		template<class T> bool operator==(Vec4<T> const& a, Vec4<T> const& b);
		template<class T> bool operator!=(Vec4<T> const& a, Vec4<T> const& b);
		template<class T> Vec4<T> operator+(Vec4<T> const& a, Vec4<T> const& b);
		template<class T> Vec4<T> operator-(Vec4<T> const& a, Vec4<T> const& b);
		template<class T> Vec4<T> operator*(Vec4<T> const& a, float b);
		template<class T> Vec4<T> operator*(Vec4<T> const& a, double b);
		template<class T> Vec4<T> operator*(Vec4<T> const& a, int b);
		template<class T> Vec4<T> operator*(float a, Vec4<T> const& b);
		template<class T> Vec4<T> operator*(double a, Vec4<T> const& b);
		template<class T> Vec4<T> operator*(int a, Vec4<T> const& b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> Vec4<T> operator / (Vec4<T> const& a, float b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> Vec4<T> operator / (Vec4<T> const& a, double b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> Vec4<T> operator / (Vec4<T> const& a, int b);
		/** Calculates the dot product of the given vectors as double. */
		template<class T> double dotd(Vec4<T> const& a, Vec4<T> const& b);
		/** Calculates the dot product of the given vectors as float. */
		template<class T> float dotf(Vec4<T> const& a, Vec4<T> const& b);
		/** Calculates the dot product of the given vectors as element type. */
		template<class T> T dot(Vec4<T> const& a, Vec4<T> const& b);
		/** Calculates the length of the given vector as double. */
		template<class T> double abs(Vec4<T> const& v);
		/** Calculates the length of the given vector as float. */
		template<class T> float absf(Vec4<T> const& v);
		/** Divides the given vector by its length. */
		template<class T> Vec4<T> norm(Vec4<T> const& a);

		template<class T, size_t sz>
		Vec4<T> avg(std::array<Vec4<T>, sz> const&);
	}
}

#include "Vector.inl"

#endif
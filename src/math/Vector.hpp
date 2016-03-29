#ifndef __re_vector_hpp_defined
#define __re_vector_hpp_defined

#include <math.h>
#include "../defines.hpp"
#include "../base_types.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		struct vec2;
		template<class T>
		struct vec3;
		template<class T>
		struct vec4;

		typedef vec2<byte> byte2, bvec2, vec2b;
		typedef vec3<byte> byte3, bvec3, vec3b;
		typedef vec4<byte> byte4, bvec4, vec4b;
		typedef vec2<ubyte> ubyte2, ubvec2, vec2ub;
		typedef vec3<ubyte> ubyte3, ubvec3, vec3ub;
		typedef vec4<ubyte> ubyte4, ubvec4, vec4ub;

		typedef vec2<float> float2, fvec2, vec2f;
		typedef vec3<float> float3, fvec3, vec3f;
		typedef vec4<float> float4, fvec4, vec4f;

		typedef vec2<int> int2, ivec2, vec2i;
		typedef vec3<int> int3, ivec3, vec3i;
		typedef vec4<int> int4, ivec4, vec4i;

		typedef vec2<short> short2, hvec2, vec2h;
		typedef vec3<short> short3, hvec3, vec3h;
		typedef vec4<short> short4, hvec4, vec4h;

		typedef vec2<unsigned int> uivec2, uint2, vec2ui;
		typedef vec3<unsigned int> uivec3, uint3, vec3ui;
		typedef vec4<unsigned int> uivec4, uint4, vec4ui;
		typedef vec2<unsigned short> uhvec2, ushort2, vec2uh;
		typedef vec3<unsigned short> uhvec3, ushort3, vec3uh;
		typedef vec4<unsigned short> uhvec4, ushort4, vec4uh;


		template<class T>
		/** Template 2-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct vec2
		{
			/** Creates a zero-vector. */
			vec2();
			/** Creates a vector with the given coordinates. */
			vec2(copy_arg_t<T> x, copy_arg_t<T> y);

			template<class U>
			/** Converts this vector to a vector of the given type. */
			REINL constexpr explicit operator vec2<U>() const;

			/** Converts this vector to a C-style array. */
			REINL constexpr operator T*();
			/** Converts this vector to a C-style array. */
			REINL constexpr operator T const*() const;

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector.*/
			T y;
		};

		template<class T>
		bool operator==(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		bool operator!=(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		vec2<T> operator+(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		vec2<T> operator-(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		vec2<T> operator*(vec2<T> const& a, float b);
		template<class T>
		vec2<T> operator*(vec2<T> const& a, double b);
		template<class T>
		vec2<T> operator*(vec2<T> const& a, int b);
		template<class T>
		vec2<T> operator*(float a, vec2<T> const&b);
		template<class T>
		vec2<T> operator*(double a, vec2<T> const& b);
		template<class T>
		vec2<T> operator*(int a, vec2<T> const& b);

		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		vec2<T> operator / (vec2<T> const& a, float b);
		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		vec2<T> operator / (vec2<T> const& a, double b);
		template<class T>
		/** Scales the given vector by the multiplicative inverse of the given number. */
		vec2<T> operator / (vec2<T> const& a, int b);
		template<class T>
		/** Calculates the dot product of the given vectors as a double. */
		double dotd(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		/** Calculates the dot product of the given vectors as a float. */
		float dotf(vec2<T> const& a, vec2<T> const& b);
		template<class T>
		/** Calculates the dot product of the given vectors as the element type of the vectors. */
		T dot(vec2<T> const& a, vec2<T> const& b);

		template<class T>
		/** Calculates the length of a vector as a double. */
		double abs(vec2<T> const& v);
		template<class T>
		/** Calculates the length of a vector as a float. */
		float absf(vec2<T> const& v);
		template<class T>
		/** Divides the given vector by its length. */
		vec2<T> norm(vec2<T> const& a);



		template<class T>
		/** Template 3-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct vec3
		{
			template<class U>
			/** Converts this vector to a vector of the given type. */
			REINL constexpr explicit operator vec3<U>() const;

			/** Creates a vector with the given coordinates. */
			vec3(copy_arg_t<T> x, copy_arg_t<T> y, copy_arg_t<T> z);
			/** Creates a zero-vector. */
			vec3();

			/** Converts this vector to a C-style array. */
			REINL constexpr operator const T*() const;
			/** Converts this vector to a C-style array. */
			REINL constexpr operator T*();

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector. */
			T y;
			/** The z (third) coordinate of the vector. */
			T z;
		};

		template<class T> bool operator==(vec3<T> const& a, vec3<T> const& b);
		template<class T> bool operator!=(vec3<T> const& a, vec3<T> const& b);
		template<class T> vec3<T> operator+(vec3<T> const& a, vec3<T> const& b);
		template<class T> vec3<T> operator-(vec3<T> const& a, vec3<T> const& b);
		template<class T> vec3<T> operator*(vec3<T> const& a, float b);
		template<class T> vec3<T> operator*(vec3<T> const& a, double b);
		template<class T> vec3<T> operator*(vec3<T> const& a, int b);
		template<class T> vec3<T> operator*(float a, vec3<T> const& b);
		template<class T> vec3<T> operator*(double a, vec3<T> const& b);
		template<class T> vec3<T> operator*(int a, vec3<T> const& b);
		template<class T> vec3<T> operator / (vec3<T> const& a, float b);
		template<class T> vec3<T> operator / (vec3<T> const& a, double b);
		template<class T> vec3<T> operator / (vec3<T> const& a, int b);
		template<class T> double dotd(vec3<T> const& a, vec3<T> const& b);
		template<class T> float dotf(vec3<T> const& a, vec3<T> const& b);
		template<class T> T dot(vec3<T> const& a, vec3<T> const& b);
		/** Calculates the length of the given vector as double. */
		template<class T> double abs(vec3<T> const& v);
		/** Calculates the length of the given vector as float. */
		template<class T> float absf(vec3<T> const& v);
		/** Calculates the cross product of the given vectors. */
		template<class T> vec3<T> cross(vec3<T> const& a, vec3<T> const& b);
		/** Divides the given vector by its length. */
		template<class T> vec3<T> norm(vec3<T> const& a);
		/** Calculates the square of the distance between the given vectors. */
		template<class T> T sqr_dist(vec3<T> const& a, vec3<T> const& b);
		/** Calculates the square of the length of the given vector. */
		template<class T> T sqr_abs(vec3<T> const& a);


		template<class T>
		/** Template 4-dimensional vector class.
			Supports conversion to element pointer, for easier passing to C functions. */
		struct vec4
		{
			template<class U>
			explicit vec4(vec4<U> const& v);

			/** Creates a 4-dimensional vector with the given coordinates.
				@param[in] xyz: The first three coordinates of the vector.
				@param[in] w: The fourth coordinate of the vector. */
			vec4(vec3<T> const& xyz, copy_arg_t<T> w);
			/** Creates a 4-dimensional vector with the given coordinates. */
			vec4(copy_arg_t<T> x, copy_arg_t<T> y, copy_arg_t<T> z, copy_arg_t<T> w);
			/** Creates a zero-vector. */
			vec4();

			/** Converts this vector to a C-style array. */
			operator const T*() const;
			/** Converts this vector to a C-style array. */
			operator T*();

			/** The x (first) coordinate of the vector. */
			T x;
			/** The y (second) coordinate of the vector. */
			T y;
			/** The z (third) coordinate of the vector. */
			T z;
			/** The w (fourth) coordinate of the vector. */
			T w;
		};

		template<class T> bool operator==(vec4<T> const& a, vec4<T> const& b);
		template<class T> bool operator!=(vec4<T> const& a, vec4<T> const& b);
		template<class T> vec4<T> operator+(vec4<T> const& a, vec4<T> const& b);
		template<class T> vec4<T> operator-(vec4<T> const& a, vec4<T> const& b);
		template<class T> vec4<T> operator*(vec4<T> const& a, float b);
		template<class T> vec4<T> operator*(vec4<T> const& a, double b);
		template<class T> vec4<T> operator*(vec4<T> const& a, int b);
		template<class T> vec4<T> operator*(float a, vec4<T> const& b);
		template<class T> vec4<T> operator*(double a, vec4<T> const& b);
		template<class T> vec4<T> operator*(int a, vec4<T> const& b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> vec4<T> operator / (vec4<T> const& a, float b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> vec4<T> operator / (vec4<T> const& a, double b);
		/** Scales the vector with the multiplicative inverse of the given number. */
		template<class T> vec4<T> operator / (vec4<T> const& a, int b);
		/** Calculates the dot product of the given vectors as double. */
		template<class T> double dotd(vec4<T> const& a, vec4<T> const& b);
		/** Calculates the dot product of the given vectors as float. */
		template<class T> float dotf(vec4<T> const& a, vec4<T> const& b);
		/** Calculates the dot product of the given vectors as element type. */
		template<class T> T dot(vec4<T> const& a, vec4<T> const& b);
		/** Calculates the length of the given vector as double. */
		template<class T> double abs(vec4<T> const& v);
		/** Calculates the length of the given vector as float. */
		template<class T> float absf(vec4<T> const& v);
		/** Divides the given vector by its length. */
		template<class T> vec4<T> norm(vec4<T> const& a);
	}
}

#include "Vector.inl"

#endif
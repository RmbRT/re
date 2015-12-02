#ifndef __re_vector_hpp_defined
#define __re_vector_hpp_defined
#include <math.h>
#include "..\defines.hpp"

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
		struct vec2
		{
			typedef T type;
			template<class U>
			explicit vec2(const vec2<U> &v);

			vec2(const T &x, const T &y);
			explicit vec2(const T v[2]);
			vec2();

			operator const T*() const;
			operator T*();

			T x, y;
		};
		
		template<class T> bool operator==(const vec2<T> &a, const vec2<T> &b);
		template<class T> bool operator!=(const vec2<T> &a, const vec2<T> &b);
		template<class T> vec2<T> operator+(const vec2<T> &a, const vec2<T> &b);
		template<class T> vec2<T> operator-(const vec2<T> &a, const vec2<T> &b);
		template<class T> vec2<T> operator*(const vec2<T> &a, float b);
		template<class T> vec2<T> operator*(const vec2<T> &a, double b);
		template<class T> vec2<T> operator*(const vec2<T> &a, int b);
		template<class T> vec2<T> operator*(float a, const vec2<T> &b);
		template<class T> vec2<T> operator*(double a, const vec2<T> &b);
		template<class T> vec2<T> operator*(int a, const vec2<T> &b);
		template<class T> vec2<T> operator / (const vec2<T> &a, float b);
		template<class T> vec2<T> operator / (const vec2<T> &a, double b);
		template<class T> vec2<T> operator / (const vec2<T> &a, int b);
		template<class T> double dotd(const vec2<T> &a, const vec2<T> &b);
		template<class T> float dotf(const vec2<T> &a, const vec2<T> &b);
		template<class T> T dot(const vec2<T> &a, const vec2<T> &b);
		template<class T> double abs(const vec2<T> &a, const vec2<T> &b);
		template<class T> float absf(const vec2<T> &a, const vec2<T> &b);
		template<class T> vec2<T> norm(const vec2<T> &a);


		template<class T>
		struct vec3
		{
			typedef T type;
			template<class U>
			explicit vec3<T>(const vec3<U> &v);
			
			vec3(const T &x, const T &y, const T &z);
			explicit vec3(const T v[3]);
			vec3();

			operator const T*() const;
			operator T*();

			T x, y, z;
		};

		template<class T> bool operator==(const vec3<T> &a, const vec3<T> &b);
		template<class T> bool operator!=(const vec3<T> &a, const vec3<T> &b);
		template<class T> vec3<T> operator+(const vec3<T> &a, const vec3<T> &b);
		template<class T> vec3<T> operator-(const vec3<T> &a, const vec3<T> &b);
		template<class T> vec3<T> operator*(const vec3<T> &a, float b);
		template<class T> vec3<T> operator*(const vec3<T> &a, double b);
		template<class T> vec3<T> operator*(const vec3<T> &a, int b);
		template<class T> vec3<T> operator*(float a, const vec3<T> &b);
		template<class T> vec3<T> operator*(double a, const vec3<T> &b);
		template<class T> vec3<T> operator*(int a, const vec3<T> &b);
		template<class T> vec3<T> operator / (const vec3<T> &a, float b);
		template<class T> vec3<T> operator / (const vec3<T> &a, double b);
		template<class T> vec3<T> operator / (const vec3<T> &a, int b);
		template<class T> double dotd(const vec3<T> &a, const vec3<T> &b);
		template<class T> float dotf(const vec3<T> &a, const vec3<T> &b);
		template<class T> T dot(const vec3<T> &a, const vec3<T> &b);
		template<class T> double abs(const vec3<T> &a, const vec3<T> &b);
		template<class T> float absf(const vec3<T> &a, const vec3<T> &b);
		template<class T> vec3<T> cross(const vec3<T> &a, const vec3<T> &b);
		template<class T> vec3<T> norm(const vec3<T> &a);
		template<class T> T sqrDist(const vec3<T> &a, const vec3<T> &b);
		template<class T> T sqrAbs(const vec3<T> &a);

		template<class T>
		struct vec4
		{
			typedef T type;
			template<class U>
			explicit vec4(const vec4<U> &v);

			vec4(const vec3<T> &xyz, const T &w);

			vec4(const T &x, const T &y, const T &z, const T &w);
			explicit vec4(const T v[4]);
			vec4();

			operator const T*() const;
			operator T*();

			T x, y, z, w;
		};

		template<class T> bool operator==(const vec4<T> &a, const vec4<T> &b);
		template<class T> bool operator!=(const vec4<T> &a, const vec4<T> &b);
		template<class T> vec4<T> operator+(const vec4<T> &a, const vec4<T> &b);
		template<class T> vec4<T> operator-(const vec4<T> &a, const vec4<T> &b);
		template<class T> vec4<T> operator*(const vec4<T> &a, float b);
		template<class T> vec4<T> operator*(const vec4<T> &a, double b);
		template<class T> vec4<T> operator*(const vec4<T> &a, int b);
		template<class T> vec4<T> operator*(float a, const vec4<T> &b);
		template<class T> vec4<T> operator*(double a, const vec4<T> &b);
		template<class T> vec4<T> operator*(int a, const vec4<T> &b);
		template<class T> vec4<T> operator / (const vec4<T> &a, float b);
		template<class T> vec4<T> operator / (const vec4<T> &a, double b);
		template<class T> vec4<T> operator / (const vec4<T> &a, int b);
		template<class T> double dotd(const vec4<T> &a, const vec4<T> &b);
		template<class T> float dotf(const vec4<T> &a, const vec4<T> &b);
		template<class T> T dot(const vec4<T> &a, const vec4<T> &b);
		template<class T> double abs(const vec4<T> &a, const vec4<T> &b);
		template<class T> float absf(const vec4<T> &a, const vec4<T> &b);
		template<class T> vec4<T> norm(const vec4<T> &a);
	}
}


#pragma region Implementation
namespace re
{
	namespace math
	{
#pragma region vec2<T>

		template<class T>
		template<class U>
		vec2<T>::vec2(const vec2<U> &v): x(v.x), y(v.y) {	}
		template<class T>
		vec2<T>::operator const T *() const
		{
			return reinterpret_cast<const T*>(this);
		}
		template<class T>
		vec2<T>::operator T*()
		{
			return reinterpret_cast<T*>(this);
		}
		template<class T>
		vec2<T>::vec2(const T &x, const T &y): x(x), y(y)	{	}
		template<class T>
		vec2<T>::vec2() : x(), y()	{	}
		template<class T>
		vec2<T>::vec2(const T v[2]): x(v[0]), y(v[1])	{	}

		template<class T>
		bool operator==(const vec2<T> &a, const vec2<T> &b)
		{
			return a.x == b.x && a.y == b.y;
		}
		template<class T>
		bool operator!=(const vec2<T> &a, const vec2<T> &b)
		{
			return a.x != b.x || a.y != b.y;
		}

		template<class T>
		vec2<T> operator + (const vec2<T> &a, const vec2<T> &b)
		{
			return vec2<T>(a.x+b.x, a.y+b.y);
		}

		template<class T>
		vec2<T> operator - (const vec2<T> &a, const vec2<T> &b)
		{
			return vec2<T>(a.x-b.x, a.y-b.y);
		}
		
		template<class T>
		vec2<T> operator * (const vec2<T> &a, float b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		vec2<T> operator * (const vec2<T> &a, double b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		vec2<T> operator * (const vec2<T> &a, int b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}

		template<class T>
		vec2<T> operator * (float a, const vec2<T> &b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		vec2<T> operator * (double a, const vec2<T> &b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		vec2<T> operator * (int a, const vec2<T> &b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}

		template<class T>
		vec2<T> operator / (const vec2<T> &a, float b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		vec2<T> operator / (const vec2<T> &a, double b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		vec2<T> operator / (const vec2<T> &a, int b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		double dotd(const vec2<T> &a, const vec2<T> &b)
		{
			return double(a.x)*double(b.x) + double(a.y)*double(b.y);
		}
		template<class T>
		float dotf(const vec2<T> &a, const vec2<T> &b)
		{
			return float(a.x)*float(b.x) + float(a.y)*float(b.y);
		}

		template<class T>
		T dot(const vec2<T> &a, const vec2<T> &b)
		{
			return a.x*b.x + a.y*b.y;
		}

		template<class T>
		double abs(const vec2<T> &v)
		{
			return sqrt(dot(v,v));
		}
		template<class T>
		float absf(const vec2<T> &v)
		{
			return sqrtf(dotf(v,v));
		}
		template<class T>
		vec2<T> norm(const vec2<T> &a)
		{
			if(a.x || a.y)
				return a/abs(a);
			else
				return a;
		}
#pragma endregion

#pragma region vec3<T>
		template<class T>
		vec3<T>::operator const T *() const
		{
			return reinterpret_cast<const T*>(this);
		}
		template<class T>
		vec3<T>::operator T*()
		{
			return reinterpret_cast<T*>(this);
		}

		template<class T>
		template<class U>
		vec3<T>::vec3(const vec3<U> &rval) : x(rval.x), y(rval.y), z(rval.z)	{	}
		template<class T>
		vec3<T>::vec3(const T &x, const T &y, const T &z) : x(x), y(y), z(z)	{	}

		template<class T>
		vec3<T>::vec3(const T v[3]) : x(v[0]), y(v[1]), z(v[2])	{	}

		template<class T>
		vec3<T>::vec3() : x(), y(), z()	{	}

		template<class T>
		bool operator==(const vec3<T> &a, const vec3<T> &b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}
		template<class T>
		bool operator!=(const vec3<T> &a, const vec3<T> &b)
		{
			return a.x != b.x || a.y != b.y || a.z != b.z;
		}

		template<class T>
		vec3<T> operator + (const vec3<T> &a, const vec3<T> &b)
		{
			return vec3<T>(a.x+b.x, a.y+b.y, a.z+b.z);
		}

		template<class T>
		vec3<T> operator - (const vec3<T> &a, const vec3<T> &b)
		{
			return vec3<T>(a.x-b.x, a.y-b.y, a.z-b.z);
		}

		template<class T>
		vec3<T> operator * (const vec3<T> &a, float b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		vec3<T> operator * (const vec3<T> &a, double b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		vec3<T> operator * (const vec3<T> &a, int b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}

		template<class T>
		vec3<T> operator * (float a, const vec3<T> &b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}
		
		template<class T>
		vec3<T> operator * (double a, const vec3<T> &b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		vec3<T> operator * (int a, const vec3<T> &b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}
		
		template<class T>
		vec3<T> operator / (const vec3<T> &a, int b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		vec3<T> operator / (const vec3<T> &a, double b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		vec3<T> operator / (const vec3<T> &a, float b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}

		template<class T>
		double dotd(const vec3<T> &a, const vec3<T> &b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z);
		}

		template<class T>
		float dotf(const vec3<T> &a, const vec3<T> &b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z);
		}
		template<class T>
		T dot(const vec3<T> &a, const vec3<T> &b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		template<class T>
		double abs(const vec3<T> &v)
		{
			return sqrt(dot(v,v));
		}

		template<class T>
		float absf(const vec3<T> &v)
		{
			return sqrtf(dotf(v,v));
		}

		template<class T>
		vec3<T> cross(const vec3<T> &a, const vec3<T> &b)
		{
			return vec3<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}

		
		template<class T>
		vec3<T> norm(const vec3<T> &a)
		{
			if(a.x || a.y || a.z)
				return a/abs(a);
			else
				return a;
		}

		template<class T>
		T sqrDist(const vec3<T> &a, const vec3<T> &b)
		{
			return sqrAbs(b-a);
		}
		template<class T>
		T sqrAbs(const vec3<T> &a)
		{
			return dot(a,a);
		}
#pragma endregion

#pragma region vec4<T>
		template<class T>
		vec4<T>::operator const T *() const
		{
			return reinterpret_cast<const T*>(this);
		}
		template<class T>
		vec4<T>::operator T*()
		{
			return reinterpret_cast<T*>(this);
		}
		template<class T>
		template<class U>
		vec4<T>::vec4(const vec4<U> &rval) : x(rval.x), y(rval.y), z(rval.z), w(rval.w)	{	}
		template<class T>
		vec4<T>::vec4(const vec3<T> &xyz, const T &w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w)	{	}
		template<class T>
		vec4<T>::vec4() : x(), y(), z(), w()	{	}
		template<class T>
		vec4<T>::vec4(const T &x, const T &y, const T &z, const T &w) : x(x), y(y), z(z), w(w)	{	}
		template<class T>
		vec4<T>::vec4(const T v[4]) : x(v[0]), y(v[1]), z(v[2]), w(v[3])	{	}


		template<class T>
		bool operator==(const vec4<T> &a, const vec4<T> &b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
		}

		template<class T>
		bool operator!=(const vec4<T> &a, const vec4<T> &b)
		{
			return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
		}

		template<class T>
		vec4<T> operator+ (const vec4<T> &a, const vec4<T> &b)
		{
			return vec4<T>(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
		}
		template<class T>
		vec4<T> operator-(const vec4<T> &a, const vec4<T> &b)
		{
			return vec4<T>(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
		}
		template<class T>
		vec4<T> operator*(float a, const vec4<T> &b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(const vec4<T> &a, float b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator*(double a, const vec4<T> &b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(const vec4<T> &a, double b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator*(int a, const vec4<T> &b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(const vec4<T> &a, int b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator/(const vec4<T> &a, int b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		vec4<T> operator/(const vec4<T> &a, float b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		vec4<T> operator/(const vec4<T> &a, double b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		double dotd(const vec4<T> &a, const vec4<T> &b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z)+double(a.w)*double(b.w);
		}
		template<class T>
		float dotf(const vec4<T> &a, const vec4<T> &b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z)+float(a.w)*float(b.w);
		}
		template<class T>
		T dot(const vec4<T> &a, const vec4<T> &b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
		}
		template<class T>
		double abs(const vec4<T> &v)
		{
			return sqrt(dot(v,v));
		}
		template<class T>
		float absf(const vec4<T> &a)
		{
			return sqrtf(dotf(a,a));
		}
		
		template<class T>
		vec4<T> norm(const vec4<T> &a)
		{
			if(a.x || a.y || a.z || a.w)
				return a/abs(a);
			else
				return a;
		}
#pragma endregion
	}
}
#pragma endregion


#endif
#include "Vector.hpp"


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
			return static_cast<const T*>(this);
		}
		template<class T>
		vec2<T>::operator T*()
		{
			return static_cast<T*>(this);
		}
		template<class T>
		vec2<T>::vec2(const T &x, const T &y): x(x), y(y)	{	}
		template<class T>
		vec2<T>::vec2() : x(), y()	{	}
		template<class T>
		vec2<T>::vec2(T v[2]): x(v[0]), y(v[1])	{	}

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
#pragma endregion

#pragma region vec3<T>
		template<class T>
		vec3<T>::operator const T *() const
		{
			return static_cast<const T*>(this);
		}
		template<class T>
		vec3<T>::operator T*()
		{
			return static_cast<T*>(this);
		}
		template<class T>
		vec3<T>::vec3(const T &x, const T &y, const T &z) : x(x), y(y), z(z)	{	}

		template<class T>
		vec3<T>::vec3(T v[3]) : x(v[0]), y(v[1]), z(v[2])	{	}

		template<class T>
		vec3<T>::vec3() : x(), y(), z()	{	}

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
#pragma endregion

#pragma region vec4<T>
		template<class T>
		vec4<T>::operator const T *() const
		{
			return static_cast<const T*>(this);
		}
		template<class T>
		vec4<T>::operator T*()
		{
			return static_cast<T*>(this);
		}
		template<class T>
		vec4<T>::vec4(): x(), y(), z(), w()	{	}
		template<class T>
		vec4<T>::vec4(const T &x, const T &y, const T &z, const T &w) : x(x), y(y), z(z), w(w)	{	}
		template<class T>
		vec4<T>::vec4(T v[4]) : x(v[0]), y(v[1]), z(v[2]), w(v[3])	{	}
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
			return sqrtf(dotf(v,v));
		}
#pragma endregion
	}
}
#pragma endregion

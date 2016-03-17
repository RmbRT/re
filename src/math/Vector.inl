namespace re
{
	namespace math
	{
		// VECTOR II

		template<class T>
		vec2<T>::vec2(copy_arg_t<T> x, copy_arg_t<T> y) :
			x(x),
			y(y)
		{
		}

		template<class T>
		template<class U>
		vec2<T>::operator vec2<U>() const
		{
			return vec2<U>(static_cast<U>(x), static_cast<U>(y));
		}

		template<class T>
		vec2<T>::operator T const*() const
		{
			return reinterpret_cast<T const*>(this);
		}

		template<class T>
		vec2<T>::operator T *()
		{
			return reinterpret_cast<T*>(this);
		}

		template<class T>
		vec2<T>::vec2(copy_arg<T> x, copy_arg<T> y) : x(), y()	{	}
		template<class T>
		vec2<T>::vec2(const T v[2]): x(v[0]), y(v[1])	{	}

		template<class T>
		bool operator==(vec2<T> const& a, vec2<T> const& b)
		{
			return a.x == b.x && a.y == b.y;
		}
		template<class T>
		bool operator!=(vec2<T> const& a, vec2<T> const& b)
		{
			return a.x != b.x || a.y != b.y;
		}

		template<class T>
		vec2<T> operator + (vec2<T> const& a, vec2<T> const& b)
		{
			return vec2<T>(a.x+b.x, a.y+b.y);
		}

		template<class T>
		vec2<T> operator - (vec2<T> const& a, vec2<T> const& b)
		{
			return vec2<T>(a.x-b.x, a.y-b.y);
		}

		template<class T>
		vec2<T> operator * (vec2<T> const& a, float b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		vec2<T> operator * (vec2<T> const& a, double b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		vec2<T> operator * (vec2<T> const& a, int b)
		{
			return vec2<T>(a.x*b, a.y*b);
		}

		template<class T>
		vec2<T> operator * (float a, vec2<T> const& b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		vec2<T> operator * (double a, vec2<T> const& b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		vec2<T> operator * (int a, vec2<T> const& b)
		{
			return vec2<T>(a*b.x, a*b.y);
		}

		template<class T>
		vec2<T> operator / (vec2<T> const& a, float b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		vec2<T> operator / (vec2<T> const& a, double b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		vec2<T> operator / (vec2<T> const& a, int b)
		{
			return vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		double dotd(vec2<T> const& a, vec2<T> const& b)
		{
			return double(a.x)*double(b.x) + double(a.y)*double(b.y);
		}
		template<class T>
		float dotf(vec2<T> const& a, vec2<T> const& b)
		{
			return float(a.x)*float(b.x) + float(a.y)*float(b.y);
		}

		template<class T>
		T dot(vec2<T> const& a, vec2<T> const& b)
		{
			return a.x*b.x + a.y*b.y;
		}

		template<class T>
		double abs(vec2<T> const& v)
		{
			return sqrt(dot(v,v));
		}
		template<class T>
		float absf(vec2<T> const& v)
		{
			return sqrtf(dotf(v,v));
		}
		template<class T>
		vec2<T> norm(vec2<T> const& a)
		{
			if(a.x || a.y)
				return a/abs(a);
			else
				return a;
		}


		// vec3


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
		vec3<T>::vec3(vec3<U> const& rval) : x(rval.x), y(rval.y), z(rval.z) {	}
		template<class T>
		vec3<T>::vec3(copy_arg_t<T> x, copy_arg_t<T> y, T z) : x(x), y(y), z(z) {	}

		template<class T>
		vec3<T>::vec3(const T v[3]) : x(v[0]), y(v[1]), z(v[2]) {	}

		template<class T>
		vec3<T>::vec3() : x(), y(), z() {	}

		template<class T>
		bool operator==(vec3<T> const& a, vec3<T> const& b)
		{
			return a.x==b.x && a.y==b.y && a.z==b.z;
		}
		template<class T>
		bool operator!=(vec3<T> const& a, vec3<T> const& b)
		{
			return a.x!=b.x||a.y!=b.y||a.z!=b.z;
		}

		template<class T>
		vec3<T> operator + (vec3<T> const& a, vec3<T> const& b)
		{
			return vec3<T>(a.x+b.x, a.y+b.y, a.z+b.z);
		}

		template<class T>
		vec3<T> operator - (vec3<T> const& a, vec3<T> const& b)
		{
			return vec3<T>(a.x-b.x, a.y-b.y, a.z-b.z);
		}

		template<class T>
		vec3<T> operator * (vec3<T> const& a, float b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		vec3<T> operator * (vec3<T> const& a, double b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		vec3<T> operator * (vec3<T> const& a, int b)
		{
			return vec3<T>(a.x*b, a.y*b, a.z*b);
		}

		template<class T>
		vec3<T> operator * (float a, vec3<T> const& b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		vec3<T> operator * (double a, vec3<T> const& b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		vec3<T> operator * (int a, vec3<T> const& b)
		{
			return vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		vec3<T> operator / (vec3<T> const& a, int b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		vec3<T> operator / (vec3<T> const& a, double b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		vec3<T> operator / (vec3<T> const& a, float b)
		{
			return vec3<T>(a.x/b, a.y/b, a.z/b);
		}

		template<class T>
		double dotd(vec3<T> const& a, vec3<T> const& b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z);
		}

		template<class T>
		float dotf(vec3<T> const& a, vec3<T> const& b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z);
		}
		template<class T>
		T dot(vec3<T> const& a, vec3<T> const& b)
		{
			return a.x*b.x+a.y*b.y+a.z*b.z;
		}

		template<class T>
		double abs(vec3<T> const& v)
		{
			return sqrt(dot(v, v));
		}

		template<class T>
		float absf(vec3<T> const& v)
		{
			return sqrtf(dotf(v, v));
		}

		template<class T>
		vec3<T> cross(vec3<T> const& a, vec3<T> const& b)
		{
			return vec3<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}


		template<class T>
		vec3<T> norm(vec3<T> const& a)
		{
			if(a.x||a.y||a.z)
				return a/abs(a);
			else
				return a;
		}

		template<class T>
		T sqrDist(vec3<T> const& a, vec3<T> const& b)
		{
			return sqrAbs(b-a);
		}
		template<class T>
		T sqrAbs(vec3<T> const& a)
		{
			return dot(a, a);
		}


		// vec4


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
		vec4<T>::vec4(vec4<U> const& rval) : x(rval.x), y(rval.y), z(rval.z), w(rval.w) {	}
		template<class T>
		vec4<T>::vec4(vec3<T> const& xyz, copy_arg_t<T> w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {	}
		template<class T>
		vec4<T>::vec4() : x(), y(), z(), w() {	}
		template<class T>
		vec4<T>::vec4(copy_arg_t<T> x, copy_arg_t<T> y, copy_arg_t<T> z, copy_arg_t<T> w):
			x(x), y(y), z(z), w(w) {	}
		template<class T>
		vec4<T>::vec4(const T v[4]) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {	}


		template<class T>
		bool operator==(vec4<T> const& a, vec4<T> const& b)
		{
			return a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w;
		}

		template<class T>
		bool operator!=(vec4<T> const& a, vec4<T> const& b)
		{
			return a.x!=b.x||a.y!=b.y||a.z!=b.z||a.w!=b.w;
		}

		template<class T>
		vec4<T> operator+ (vec4<T> const& a, vec4<T> const& b)
		{
			return vec4<T>(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
		}
		template<class T>
		vec4<T> operator-(vec4<T> const& a, vec4<T> const& b)
		{
			return vec4<T>(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
		}
		template<class T>
		vec4<T> operator*(float a, vec4<T> const& b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(vec4<T> const& a, float b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator*(double a, vec4<T> const& b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(vec4<T> const& a, double b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator*(int a, vec4<T> const& b)
		{
			return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		vec4<T> operator*(vec4<T> const& a, int b)
		{
			return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		vec4<T> operator/(vec4<T> const& a, int b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		vec4<T> operator/(vec4<T> const& a, float b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		vec4<T> operator/(vec4<T> const& a, double b)
		{
			return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		double dotd(vec4<T> const& a, vec4<T> const& b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z)+double(a.w)*double(b.w);
		}
		template<class T>
		float dotf(vec4<T> const& a, vec4<T> const& b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z)+float(a.w)*float(b.w);
		}
		template<class T>
		T dot(vec4<T> const& a, vec4<T> const& b)
		{
			return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
		}
		template<class T>
		double abs(vec4<T> const& v)
		{
			return sqrt(dot(v, v));
		}
		template<class T>
		float absf(vec4<T> const& a)
		{
			return sqrtf(dotf(a, a));
		}

		template<class T>
		vec4<T> norm(vec4<T> const& a)
		{
			if(a.x||a.y||a.z||a.w)
				return a/abs(a);
			else
				return a;
		}

	}
}

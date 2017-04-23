namespace re
{
	namespace math
	{
		// VECTOR II

		template<class T>
		RECX Vec2<T>::Vec2():
			x(),
			y()
		{
		}
		template<class T>
		RECX Vec2<T>::Vec2(copy_arg_t<T> x, copy_arg_t<T> y) :
			x(x),
			y(y)
		{
		}

		template<class T>
		RECX Vec2<T>::Vec2(Vec3<T> const& v):
			x(v.x),
			y(v.y)
		{
		}

		template<class T>
		RECX Vec2<T>::Vec2(Vec4<T> const& v):
			x(v.x),
			y(v.y)
		{
		}

		template<class T>
		RECX Vec3<T>::Vec3(Vec4<T> const& v):
			x(v.x),
			y(v.y),
			z(v.z)
		{
		}

		template<class T>
		template<class U>
		RECX Vec2<T>::operator Vec2<U>() const
		{
			return Vec2<U>(static_cast<U>(x), static_cast<U>(y));
		}

		template<class T>
		RECX Vec2<T>::operator T const*() const
		{
			return reinterpret_cast<T const*>(this);
		}

		template<class T>
		RECX14 Vec2<T>::operator T *()
		{
			return reinterpret_cast<T*>(this);
		}

		template<class T>
		RECX bool operator==(Vec2<T> const& a, Vec2<T> const& b)
		{
			return a.x == b.x && a.y == b.y;
		}
		template<class T>
		RECX bool operator!=(Vec2<T> const& a, Vec2<T> const& b)
		{
			return a.x != b.x || a.y != b.y;
		}

		template<class T>
		RECX Vec2<T> operator + (Vec2<T> const& a, Vec2<T> const& b)
		{
			return Vec2<T>(a.x+b.x, a.y+b.y);
		}

		template<class T>
		RECX Vec2<T> operator - (Vec2<T> const& a, Vec2<T> const& b)
		{
			return Vec2<T>(a.x-b.x, a.y-b.y);
		}

		template<class T>
		RECX Vec2<T> operator * (Vec2<T> const& a, float b)
		{
			return Vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		RECX Vec2<T> operator * (Vec2<T> const& a, double b)
		{
			return Vec2<T>(a.x*b, a.y*b);
		}
		template<class T>
		RECX Vec2<T> operator * (Vec2<T> const& a, int b)
		{
			return Vec2<T>(a.x*b, a.y*b);
		}

		template<class T>
		RECX Vec2<T> operator * (float a, Vec2<T> const& b)
		{
			return Vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		RECX Vec2<T> operator * (double a, Vec2<T> const& b)
		{
			return Vec2<T>(a*b.x, a*b.y);
		}
		template<class T>
		RECX Vec2<T> operator * (int a, Vec2<T> const& b)
		{
			return Vec2<T>(a*b.x, a*b.y);
		}

		template<class T>
		RECX Vec2<T> operator / (Vec2<T> const& a, float b)
		{
			return Vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		RECX Vec2<T> operator / (Vec2<T> const& a, double b)
		{
			return Vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		RECX Vec2<T> operator / (Vec2<T> const& a, int b)
		{
			return Vec2<T>(a.x/b, a.y/b);
		}
		template<class T>
		RECX double dotd(Vec2<T> const& a, Vec2<T> const& b)
		{
			return double(a.x)*double(b.x) + double(a.y)*double(b.y);
		}
		template<class T>
		RECX float dotf(Vec2<T> const& a, Vec2<T> const& b)
		{
			return float(a.x)*float(b.x) + float(a.y)*float(b.y);
		}

		template<class T>
		RECX T dot(Vec2<T> const& a, Vec2<T> const& b)
		{
			return a.x*b.x + a.y*b.y;
		}

		template<class T>
		double abs(Vec2<T> const& v)
		{
			return sqrt(dot(v,v));
		}
		template<class T>
		float absf(Vec2<T> const& v)
		{
			return sqrtf(dotf(v,v));
		}
		template<class T>
		RECX Vec2<T> norm(Vec2<T> const& a)
		{
			return a.x || a.y ? a/abs(a) : a;
		}

		namespace detail
		{
			template<class T>
			using avg_accum_t = decltype(T()+T());
		}



		template<class T, size_t sz>
		Vec2<T> avg(std::array<Vec2<T>, sz> const& arr)
		{
			detail::avg_accum_t<T> accx(0), accy(0);
			for(size_t i = sz; i--;)
			{
				accx += arr[i].x;
				accy += arr[i].y;
			}
			if(sz)
				return Vec2<T>( accx / sz, accy / sz );
			else
				return Vec2<T>(0,0);
		}

		template<class T, size_t sz>
		Vec3<T> avg(std::array<Vec3<T>, sz> const& arr)
		{
			detail::avg_accum_t<T> accx(0), accy(0), accz(0);
			for(size_t i = sz; i--;)
			{
				accx += arr[i].x;
				accy += arr[i].y;
				accz += arr[i].z;
			}
			if(sz)
				return Vec3<T>( accx / sz, accy / sz, accz / sz);
			else
				return Vec3<T>(0,0,0);
		}

		template<class T, size_t sz>
		Vec4<T> avg(std::array<Vec4<T>, sz> const& arr)
		{
			detail::avg_accum_t<T> accx(0), accy(0), accz(0), accw(0);
			for(size_t i = sz; i--;)
			{
				accx += arr[i].x;
				accy += arr[i].y;
				accz += arr[i].z;
				accw += arr[i].w;
			}
			if(sz)
				return Vec4<T>( accx / sz, accy / sz, accz / sz);
			else
				return Vec4<T>(0,0,0,0);
		}

		// Vec3


		template<class T>
		RECX Vec3<T>::operator const T *() const
		{
			return reinterpret_cast<const T*>(this);
		}
		template<class T>
		RECX14 Vec3<T>::operator T*()
		{
			return reinterpret_cast<T*>(this);
		}


		template<class T>
		RECX Vec3<T>::Vec3(
			copy_arg_t<T> x,
			copy_arg_t<T> y,
			copy_arg_t<T> z):
			x(x),
			y(y),
			z(z)
		{
		}

		template<class T>
		template<class U>
		RECX Vec3<T>::operator Vec3<U>() const
		{
			return {x,y,z};
		}

		template<class T>
		RECX Vec3<T>::Vec3() : x(), y(), z() {	}

		template<class T>
		bool operator==(Vec3<T> const& a, Vec3<T> const& b)
		{
			return a.x==b.x && a.y==b.y && a.z==b.z;
		}
		template<class T>
		bool operator!=(Vec3<T> const& a, Vec3<T> const& b)
		{
			return a.x!=b.x||a.y!=b.y||a.z!=b.z;
		}

		template<class T>
		Vec3<T> operator + (Vec3<T> const& a, Vec3<T> const& b)
		{
			return Vec3<T>(a.x+b.x, a.y+b.y, a.z+b.z);
		}

		template<class T>
		Vec3<T> operator - (Vec3<T> const& a, Vec3<T> const& b)
		{
			return Vec3<T>(a.x-b.x, a.y-b.y, a.z-b.z);
		}

		template<class T>
		Vec3<T> operator * (Vec3<T> const& a, float b)
		{
			return Vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		Vec3<T> operator * (Vec3<T> const& a, double b)
		{
			return Vec3<T>(a.x*b, a.y*b, a.z*b);
		}
		template<class T>
		Vec3<T> operator * (Vec3<T> const& a, int b)
		{
			return Vec3<T>(a.x*b, a.y*b, a.z*b);
		}

		template<class T>
		Vec3<T> operator * (float a, Vec3<T> const& b)
		{
			return Vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		Vec3<T> operator * (double a, Vec3<T> const& b)
		{
			return Vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		Vec3<T> operator * (int a, Vec3<T> const& b)
		{
			return Vec3<T>(a*b.x, a*b.y, a*b.z);
		}

		template<class T>
		Vec3<T> operator / (Vec3<T> const& a, int b)
		{
			return Vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		Vec3<T> operator / (Vec3<T> const& a, double b)
		{
			return Vec3<T>(a.x/b, a.y/b, a.z/b);
		}
		template<class T>
		Vec3<T> operator / (Vec3<T> const& a, float b)
		{
			return Vec3<T>(a.x/b, a.y/b, a.z/b);
		}

		template<class T>
		double dotd(Vec3<T> const& a, Vec3<T> const& b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z);
		}

		template<class T>
		float dotf(Vec3<T> const& a, Vec3<T> const& b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z);
		}
		template<class T>
		T dot(Vec3<T> const& a, Vec3<T> const& b)
		{
			return a.x*b.x+a.y*b.y+a.z*b.z;
		}

		template<class T>
		double abs(Vec3<T> const& v)
		{
			return sqrt(dot(v, v));
		}

		template<class T>
		float absf(Vec3<T> const& v)
		{
			return sqrtf(dotf(v, v));
		}

		template<class T>
		Vec3<T> cross(Vec3<T> const& a, Vec3<T> const& b)
		{
			return Vec3<T>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}


		template<class T>
		Vec3<T> norm(Vec3<T> const& a)
		{
			if(a.x||a.y||a.z)
				return a/abs(a);
			else
				return a;
		}

		template<class T>
		T sqr_dist(Vec3<T> const& a, Vec3<T> const& b)
		{
			return sqrAbs(b-a);
		}
		template<class T>
		T sqr_abs(Vec3<T> const& a)
		{
			return dot(a, a);
		}


		// Vec4


		template<class T>
		RECX Vec4<T>::operator const T *() const
		{
			return reinterpret_cast<const T*>(this);
		}
		template<class T>
		RECX14 Vec4<T>::operator T*()
		{
			return reinterpret_cast<T*>(this);
		}
		template<class T>
		template<class U>
		RECX Vec4<T>::operator Vec4<U>(void) const
		{
			return Vec4<U>(x,y,z,w);
		}
		template<class T>
		RECX Vec4<T>::Vec4(Vec3<T> const& xyz, copy_arg_t<T> w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {	}
		template<class T>
		RECX Vec4<T>::Vec4() : x(), y(), z(), w() {	}

		template<class T>
		RECX Vec4<T>::Vec4(
			copy_arg_t<T> x,
			copy_arg_t<T> y,
			copy_arg_t<T> z,
			copy_arg_t<T> w):
			x(x),
			y(y),
			z(z),
			w(w)
		{
		}


		template<class T>
		bool operator==(Vec4<T> const& a, Vec4<T> const& b)
		{
			return a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w;
		}

		template<class T>
		bool operator!=(Vec4<T> const& a, Vec4<T> const& b)
		{
			return a.x!=b.x||a.y!=b.y||a.z!=b.z||a.w!=b.w;
		}

		template<class T>
		Vec4<T> operator+ (Vec4<T> const& a, Vec4<T> const& b)
		{
			return Vec4<T>(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
		}
		template<class T>
		Vec4<T> operator-(Vec4<T> const& a, Vec4<T> const& b)
		{
			return Vec4<T>(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
		}
		template<class T>
		Vec4<T> operator*(float a, Vec4<T> const& b)
		{
			return Vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		Vec4<T> operator*(Vec4<T> const& a, float b)
		{
			return Vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		Vec4<T> operator*(double a, Vec4<T> const& b)
		{
			return Vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		Vec4<T> operator*(Vec4<T> const& a, double b)
		{
			return Vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		Vec4<T> operator*(int a, Vec4<T> const& b)
		{
			return Vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w);
		}
		template<class T>
		Vec4<T> operator*(Vec4<T> const& a, int b)
		{
			return Vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b);
		}
		template<class T>
		Vec4<T> operator/(Vec4<T> const& a, int b)
		{
			return Vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		Vec4<T> operator/(Vec4<T> const& a, float b)
		{
			return Vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		Vec4<T> operator/(Vec4<T> const& a, double b)
		{
			return Vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b);
		}
		template<class T>
		double dotd(Vec4<T> const& a, Vec4<T> const& b)
		{
			return double(a.x)*double(b.x)+double(a.y)*double(b.y)+double(a.z)*double(b.z)+double(a.w)*double(b.w);
		}
		template<class T>
		float dotf(Vec4<T> const& a, Vec4<T> const& b)
		{
			return float(a.x)*float(b.x)+float(a.y)*float(b.y)+float(a.z)*float(b.z)+float(a.w)*float(b.w);
		}
		template<class T>
		T dot(Vec4<T> const& a, Vec4<T> const& b)
		{
			return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
		}
		template<class T>
		double abs(Vec4<T> const& v)
		{
			return sqrt(dot(v, v));
		}
		template<class T>
		float absf(Vec4<T> const& a)
		{
			return sqrtf(dotf(a, a));
		}

		template<class T>
		Vec4<T> norm(Vec4<T> const& a)
		{
			if(a.x||a.y||a.z||a.w)
				return a/abs(a);
			else
				return a;
		}

	}
}

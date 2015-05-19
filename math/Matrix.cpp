#include "Matrix.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		mat2x2<T> mat2x2<T>::IDENTITY = mat2x2<T>(1,0,0,1);

		template<class T>
		mat3x3<T> mat3x3<T>::IDENTITY = mat3x3<T>(1,0,0,0,1,0,0,0,1);

		template<class T>
		mat4x4<T> mat4x4<T>::IDENTITY = mat4x4<T>(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);


		template<class T>
		template<class U>
		mat2x2<T>::mat2x2(const mat2x2<U> &m) : v0(m.v0), v1(m.v1)	{	}

		template<class T>
		mat2x2<T>::mat2x2(const T &v00, const T &v10, const T &v01, const T &v11): v0(v00, v01), v1(v10, v11)	{	}

		template<class T>
		mat2x2<T>::mat2x2(const vec2<T> &v0, const vec2<T> &v1) : v0(v0), v1(v1)	{	}

		template<class T>
		template<class U>
		mat3x3<T>::mat3x3(const mat3x3<U> &m) : v0(m.v0), v1(m.v1), v2(m.v2)	{	}

		template<class T>
		mat3x3<T>::mat3x3(const T &v00, const T &v10, const T &v20,
			const T &v01, const T &v11, const T &v21,
			const T &v02, const T &v12, const T &v22): v0(v00, v01, v02), v1(v10, v11, v12), v2(v20, v21, v22)	{	}

		template<class T>
		mat3x3<T>::mat3x3(const vec3<T> &v0, const vec3<T> &v1, const vec3<T> &v2) : v0(v0), v1(v1), v2(v2)	{	}

		template<class T>
		template<class U>
		mat4x4<T>::mat4x4(const mat4x4<U> &m): v0(m.v0), v1(m.v1), v2(m.v2), v3(m.v3)	{	}

		template<class T>
		mat4x4<T>::mat4x4(const T &v00, const T &v10, const T &v20, const T &v30,
			const T &v01, const T &v11, const T &v21, const T &v31,
			const T &v02, const T &v12, const T &v22, const T &v32,
			const T &v03, const T &v13, const T &v23, const T &v33)
			: v0(v00, v01, v02, v03), v1(v10, v11, v12, v13), v2(v20, v21, v22, v23), v3(v30, v31, v32, v33)	{	}

		template<class T>
		mat4x4<T>::mat4x4(const vec4<T> &v0, const vec4<T> &v1, const vec4<T> &v2, const vec4<T> &v3): v0(v0), v1(v1), v2(v2), v3(v3)	{	}
	}
}
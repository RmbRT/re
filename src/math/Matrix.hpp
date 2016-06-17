#ifndef __re_matrix_hpp_defined
#define __re_matrix_hpp_defined

#include "Vector.hpp"
#include "Angle.hpp"
#include "Ray.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		struct mat2x2;
		template<class T>
		struct mat3x3;
		template<class T>
		struct mat4x4;

		typedef mat2x2<float> float2x2, fmat2x2, mat2x2f;
		typedef mat3x3<float> float3x3, fmat3x3, mat3x3f;
		typedef mat4x4<float> float4x4, fmat4x4, mat4x4f;

		typedef mat2x2<int> int2x2, imat2x2, mat2x2i;
		typedef mat3x3<int> int3x3, imat3x3, mat3x3i;
		typedef mat4x4<int> int4x4, imat4x4, mat4x4i;

		typedef mat2x2<short> short2x2, hmat2x2, mat2x2h;
		typedef mat3x3<short> short3x3, hmat3x3, mat3x3h;
		typedef mat4x4<short> short4x4, hmat4x4, mat4x4h;

		/*The element tpye of the matrix.*/
		template<class T>
		/*Represents a 2x2 matrix. The values are stored column-wise.*/
		struct mat2x2
		{
			/*Converts a 2x2 matrix of one type to another.*/
			template<class U>
			explicit mat2x2<T>(const mat2x2<U> &m);

			/*Constructs a 2x2 matrix. The values are passed row-wise.*/
			mat2x2(const T& v00, const T &v10, const T &v01, const T &v11);

			/*Constructs a 2x2 matrix with the given columns.
			@param[in] v0: the first column of the matrix.
			@param[in] v1: the second column of the matrix.*/
			mat2x2(const vec2<T> &v0, const vec2<T> &v1);


			mat2x2<T> operator*(const mat2x2<T> &rval) const;
			vec2<T> operator*(const vec2<T> &rval) const;

			bool operator==(const mat2x2<T> &other) const;
			bool operator!=(const mat2x2<T> &other) const;

			static const mat2x2<T> IDENTITY;

			/*The columns of the matrix.*/
			vec2<T> v0, v1;
		};

		template<class T>
		mat2x2<T> operator*(float a, const mat2x2<T> &b);

		/*The element type of the matrix.*/
		template<class T>
		/*Represents a 3x3 matrix. The values are stored column-wise.*/
		struct mat3x3
		{
			/*Converts a 3x3 matrix of one type to another.*/
			template<class U>
			explicit mat3x3<T>(const mat3x3<U> &m);

			/*Constructs a 3x3 matrix. The values are passed row-wise.*/
			mat3x3(const T &v00, const T &v10, const T &v20,
				const T &v01, const T &v11, const T &v21,
				const T &v02, const T &v12, const T &v22);

			/*Constructs a 3x3 matrix with the given columns.
			@param[in] v0: the first column of the matrix.
			@param[in] v1: the second column of the matrix.
			@param[in] v2: the third column of the matrix.*/
			mat3x3(const vec3<T> &v0, const vec3<T> &v1, const vec3<T> &v2);

			mat3x3<T> operator*(const mat3x3<T> &rval) const;
			vec3<T> operator*(const vec3<T> &rval) const;

			bool operator==(const mat3x3<T> &other) const;
			bool operator!=(const mat3x3<T> &other) const;

			static const mat3x3<T> IDENTITY;

			/*The columns of the matrix.*/
			vec3<T> v0, v1, v2;
		};

		template<class T>
		mat3x3<T> operator*(float a, const mat3x3<T> &b);

		/*The element type of the matrix.*/
		template<class T>
		/*Represents a 4x4 matrix. The values are stored column-wise.*/
		struct mat4x4
		{
			/*Converts a 4x4 matrix of one type to another.*/
			template<class U>
			explicit mat4x4(const mat4x4<U> &m);

			/*Constructs a 4x4 matrix. The values are passed row-wise.*/
			mat4x4(const T &v00, const T &v10, const T &v20, const T &v30,
				const T &v01, const T &v11, const T &v21, const T &v31,
				const T &v02, const T &v12, const T &v22, const T &v32,
				const T &v03, const T &v13, const T &v23, const T &v33);

			/*Constructs a 4x4 matrix with the given columns.
			@param[in] v0: the first column of the matrix.
			@param[in] v1: the second column of the matrix.
			@param[in] v2: the third column of the matrix.
			@param[in] v3: the fourth column of the matrix.*/
			mat4x4(const vec4<T> &v0, const vec4<T> &v1, const vec4<T> &v2, const vec4<T> &v3);

			mat4x4<T> operator*(const mat4x4<T> &rval) const;
			vec4<T> operator*(const vec4<T> &rval) const;
			Ray<T> operator*(const Ray<T> &val) const;

			bool operator==(const mat4x4<T> &other) const;
			bool operator!=(const mat4x4<T> &other) const;

			static mat4x4<T> transform(const vec3<T> &xAxis, const vec3<T> &yAxis, const vec3<T> &zAxis, const vec3<T> &translate);
			static mat4x4<T> lookAt(const vec3<T> &pos, const vec3<T> &forward, const vec3<T> &up);
			static mat4x4<T> rotationX(const Angle &alpha);
			static mat4x4<T> rotationY(const Angle &alpha);
			static mat4x4<T> rotationZ(const Angle &alpha);
			static mat4x4<T> translation(const vec3<T> &delta);
			static mat4x4<T> ortho(T width, T height, T zNear, T zFar);
			static mat4x4<T> ortho(T xmin, T ymin, T xmax, T ymax, T zNear, T zFar);
			static mat4x4<T> ortho_infinite(T width, T height);
			static mat4x4<T> ortho_infinite(T xmin, T ymin, T xmax, T ymax);
			static mat4x4<T> perspective(const Angle &yFov, T width, T height, T zNear, T zFar);
			static mat4x4<T> rotation(const vec3<Angle> &rotation);
			static mat4x4<T> scaling(const vec3<T> &scaling);
			static mat4x4<T> transformation(const vec3<T> &position, const vec3<Angle> &rotation, const vec3<T> &scaling);
			/*Kind of hacky, but works. Also, does not use inverse matrix method. maybe inverse is faster but idk.*/
			static mat4x4<T> inverse_lookAt(const mat4x4<T> &look_at);

			static const mat4x4<T> IDENTITY;

			/*The columns of the matrix.*/
			vec4<T> v0, v1, v2, v3;
		};

		template<class T>
		mat4x4<T> operator*(float a, const mat4x4<T> &b);
	}
}

#pragma region Implementation
namespace re
{
	namespace math
	{
		template<class T>
		const mat2x2<T> mat2x2<T>::IDENTITY = mat2x2<T>(1,0,0,1);

		template<class T>
		const mat3x3<T> mat3x3<T>::IDENTITY = mat3x3<T>(1,0,0,0,1,0,0,0,1);

		template<class T>
		const mat4x4<T> mat4x4<T>::IDENTITY = mat4x4<T>(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

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

		template<class T>
		mat2x2<T> mat2x2<T>::operator*(const mat2x2<T> &rval) const
		{
			vec2<T> r0(v0.x, v1.x),
					r1(v0.y, v1.y);

			return mat2x2<T>(dot(r0, rval.v0), dot(r0, rval.v1),
							 dot(r1, rval.v0), dot(r1, rval.v1));
		}

		template<class T>
		mat3x3<T> mat3x3<T>::operator*(const mat3x3<T> &rval) const
		{
			vec3<T> r0(v0.x, v1.x, v2.x),
					r1(v0.y, v1.y, v2.y),
					r2(v0.z, v1.z, v2.z);
			return mat3x3<T>(dot(r0, rval.v0), dot(r0, rval.v1), dot(r0, rval.v2),
							 dot(r1, rval.v0), dot(r1, rval.v1), dot(r1, rval.v2),
							 dot(r2, rval.v0), dot(r2, rval.v1), dot(r2, rval.v2));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::operator*(const mat4x4<T> &rval) const
		{
			vec4<T> r0(v0.x, v1.x, v2.x, v3.x),
					r1(v0.y, v1.y, v2.y, v3.y),
					r2(v0.z, v1.z, v2.z, v3.z),
					r3(v0.w, v1.w, v2.w, v3.w);
			return mat4x4<T>(dot(r0, rval.v0), dot(r0, rval.v1), dot(r0, rval.v2), dot(r0, rval.v3),
							 dot(r1, rval.v0), dot(r1, rval.v1), dot(r1, rval.v2), dot(r1, rval.v3),
							 dot(r2, rval.v0), dot(r2, rval.v1), dot(r2, rval.v2), dot(r2, rval.v3),
							 dot(r3, rval.v0), dot(r3, rval.v1), dot(r3, rval.v2), dot(r3, rval.v3));
		}

		template<class T>
		vec2<T> mat2x2<T>::operator*(const vec2<T> &rval) const
		{
			vec2<T> r0(v0.x, v1.x),
					r1(v0.y, v1.y);
			return vec2<T>(dot(r0, rval),
						   dot(r1, rval));
		}
		template<class T>
		vec3<T> mat3x3<T>::operator*(const vec3<T> &rval) const
		{
			vec3<T> r0(v0.x, v1.x, v2.x),
					r1(v0.y, v1.y, v2.y),
					r2(v0.z, v1.z, v2.z);
			return vec3<T>(dot(r0,rval),
						   dot(r1,rval),
						   dot(r2,rval));
		}
		template<class T>
		vec4<T> mat4x4<T>::operator*(const vec4<T> &rval) const
		{
			vec4<T> r0(v0.x, v1.x, v2.x, v3.x),
					r1(v0.y, v1.y, v2.y, v3.y),
					r2(v0.z, v1.z, v2.z, v3.z),
					r3(v0.w, v1.w, v2.w, v3.w);
			return vec4<T>(dot(r0,rval),
						   dot(r1,rval),
						   dot(r2,rval),
						   dot(r3,rval));
		}

		template<class T>
		Ray<T> mat4x4<T>::operator*(const Ray<T> &rval) const
		{
			return Ray<T>(vec3<T>(operator*(vec4<T>(rval.position,1))), vec3<T>(operator*(vec4<T>(rval.direction,0))));
		}

		template<class T>
		mat2x2<T> operator*(float a, const mat2x2<T> &b)
		{
			return mat2x2<T>(a*b.v0, a*b.v1);
		}
		template<class T>
		mat3x3<T> operator*(float a, const mat3x3<T> &b)
		{
			return mat3x3<T>(a*b.v0, a*b.v1, a*b.v2);
		}
		template<class T>
		mat4x4<T> operator*(float a, const mat4x4<T> &b)
		{
			return mat4x4<T>(a*b.v0, a*b.v1, a*b.v2, a*b.v3);
		}


		template<class T>
		bool mat2x2<T>::operator==(const mat2x2<T> &other) const
		{
			return v0 == other.v0 && v1 == other.v1;
		}
		template<class T>
		bool mat3x3<T>::operator==(const mat3x3<T> &other) const
		{
			return v0 == other.v0 && v1 == other.v1 && v2 == other.v2;
		}
		template<class T>
		bool mat4x4<T>::operator==(const mat4x4<T> &other) const
		{
			return v0 == other.v0 && v1 == other.v1 && v2 == other.v2 && v3 == other.v3;
		}

		template<class T>
		bool mat2x2<T>::operator!=(const mat2x2<T> &other) const
		{
			return v0 != other.v0 || v1 != other.v1;
		}
		template<class T>
		bool mat3x3<T>::operator!=(const mat3x3<T> &other) const
		{
			return v0 != other.v0 || v1 != other.v1 || v2 != other.v2;
		}
		template<class T>
		bool mat4x4<T>::operator!=(const mat4x4<T> &other) const
		{
			return v0 != other.v0 || v1 != other.v1 || v2 != other.v2 || v3 != other.v3;
		}

		template<class T>
		mat4x4<T> mat4x4<T>::transform(const vec3<T> &xAxis, const vec3<T> &yAxis, const vec3<T> &zAxis, const vec3<T> &translate)
		{
			vec4<T> v0(xAxis, 0),
				v1 (yAxis, 0),
				v2 (zAxis, 0),
				v3 (translate, 1);
			return mat4x4<T>(v0, v1, v2, v3);
		}
		template<class T>
		mat4x4<T> mat4x4<T>::lookAt(const vec3<T> &position, const vec3<T> &forward, const vec3<T> &up)
		{
			/*vec3<T> _z(norm(forward));
			vec3<T> _x(norm(cross(up,forward)));
			vec3<T> _y(norm(cross(forward, _x)));
			vec4<T> x(_z.x, _z.y, _z.z, -dot(_x,position));
			return mat4x4<T>(_x.x, _y.x, _z.x, -dot(_x,position),
							 _x.y, _y.y, _z.y, -dot(_y,position),
							 _x.z, _y.z, _z.z, -dot(_z,position),
							 0, 0, 0, 1);*/
			vec3<T> _z(norm(forward));
			vec3<T> _x(norm(cross(up,_z)));
			vec3<T> _y(norm(cross(_z,_x)));
			return mat4x4<T>(vec4<T>(_x.x, _y.x, _z.x, 0),
							 vec4<T>(_x.y, _y.y, _z.y, 0),
							 vec4<T>(_x.z, _y.z, _z.z, 0),
							 vec4<T>(-dot(_x, position), -dot(_y, position), -dot(_z, position), 1));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::rotationX(const Angle &alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return mat4x4<T>(1, 0, 0, 0,
							 0, c,-s, 0,
							 0, s, c, 0,
							 0, 0, 0, 1);
		}
		template<class T>
		mat4x4<T> mat4x4<T>::rotationY(const Angle &alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return mat4x4<T>(c, 0, s, 0,
							 0, 1, 0, 0,
							 -s,0, c, 0,
							 0, 0, 0, 1);
		}
		template<class T>
		mat4x4<T> mat4x4<T>::rotationZ(const Angle &alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return mat4x4<T>(c,-s, 0, 0,
							 s, c, 0, 0,
							 0, 0, 1, 0,
							 0, 0, 0, 1);
		}

		template<class T>
		mat4x4<T> mat4x4<T>::translation(const vec3<T> &delta)
		{
			return mat4x4<T>(1, 0, 0, delta.x,
							 0, 1, 0, delta.y,
							 0, 0, 1, delta.z,
							 0, 0,	0, 1);
		}

		template<class T>
		mat4x4<T> mat4x4<T>::ortho(T width, T height, T zNear, T zFar)
		{
			T inv = T(-1)/(zFar-zNear);
			return mat4x4<T>(
				vec4<T>(1/width, 0, 0, 0),
				vec4<T>(0, 1/height, 0, 0),
				vec4<T>(0, 0, inv+inv, (zFar+zNear)*inv),
				vec4<T>(0, 0, 0, 1));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::ortho(T xmin, T ymin, T xmax, T ymax, T zNear, T zFar)
		{
			T w = (xmax-xmin)/2;
			T h = (ymax-ymin)/2;
			return ortho(w, h, zNear, zFar)*translation(vec3<T>(-xmin-w, -ymin+h, 0));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::ortho_infinite(T width, T height)
		{
			return mat4x4<T>(
				vec4<T>(1/width, 0, 0, 0),
				vec4<T>(0, 1/height, 0, 0),
				vec4<T>(0, 0, 0, 0),
				vec4<T>(0, 0, 0, 1));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::ortho_infinite(T xmin, T ymin, T xmax, T ymax)
		{
			return ortho_infinite((xmax-xmin)/2, (ymax-ymin)/2) * translation(vec3<T>(-xmin,-ymin,0));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::perspective(const Angle &yFov, T width, T height, T zNear, T zFar)
		{
			/*T inv = T(1)/(zNear-zFar);
			T t = (zNear*zFar)*inv;
			T _tan = T(1)/tan(yFov/T(2));
			T aspect = height / width;
			T xFov = _tan * aspect;

			return mat4x4<T>(xFov, 0,    0,                0,
							 0,    _tan, 0,                0,
							 0,    0,    (zFar+zNear)*inv, T(2)*(zNear*zFar)*inv,
							 0,    0,    1,                0);*/

			/*const T ar = height / width;
			const T tanHalfFOV = T(1)/tan(yFov/T(2));
			const T zRange = T(1)/(zNear - zFar);

			return mat4x4<T>(
				vec4<T>(ar*tanHalfFOV, T(0), T(0), T(0)),
				vec4<T>(T(0), tanHalfFOV, T(0), T(0)),
				vec4<T>(T(0), T(0), T(-zNear-zFar)*zRange, T(2)*zFar*zNear*zRange),
				vec4<T>(T(0), T(0), T(1), T(0)));*/

			const T _tan = T(1)/tan(rad(yFov.rad() * T(0.5)));
			const T AR = height / width;
			const T A = AR * _tan;
			const T &B = _tan;
			const T C = zFar / (zFar-zNear);
			const T D = T(1);
			const T E = -zNear * C;

			return mat4x4<T>(
				vec4<T>(A,0,0,0),
				vec4<T>(0,B,0,0),
				vec4<T>(0,0,C,D),
				vec4<T>(0,0,E,0));
		}

		template<class T>
		mat4x4<T> mat4x4<T>::rotation(const vec3<Angle> &axis)
		{
			return rotationZ(axis.z)*rotationY(axis.y)*rotationX(axis.x);
		}


		template<class T>
		mat4x4<T> mat4x4<T>::scaling(const vec3<T> &scaling)
		{
			return mat4x4<T>(scaling.x,0,0,0,
							 0,scaling.y,0,0,
							 0,0,scaling.z,0,
							 0,0,0,1);
		}

		template<class T>
		mat4x4<T> mat4x4<T>::transformation(const vec3<T> &position, const vec3<Angle> &rotation, const vec3<T> &scaling)
		{
			return translation(position) * mat4x4<T>::rotation(rotation) * mat4x4<T>::scaling(scaling);
		}

		template<class T>
		mat4x4<T> mat4x4<T>::inverse_lookAt(const mat4x4<T> &look_at)
		{
			const math::fvec3 origin = math::fvec3(look_at * math::fvec4(0,0,0,1));
			const math::fvec3 up = math::fvec3(look_at * math::fvec4(0,1,0,1)) - origin;
			const math::fvec3 forward = math::fvec3(look_at * math::fvec4(0,0,1,1)) - origin;

			const math::fmat4x4 inv_view = math::fmat4x4::lookAt(origin, forward, up);
			return inv_view;
		}
	}
}

#pragma endregion

#endif
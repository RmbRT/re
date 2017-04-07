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
		struct Mat2x2;
		template<class T>
		struct Mat3x3;
		template<class T>
		struct Mat4x4;

		typedef Mat2x2<float> float2x2_t, fmat2x2_t, mat2x2f_t;
		typedef Mat3x3<float> float3x3_t, fmat3x3_t, mat3x3f_t;
		typedef Mat4x4<float> float4x4_t, fmat4x4_t, mat4x4f_t;

		typedef Mat2x2<int> int2x2_t, imat2x2_t, mat2x2i_t;
		typedef Mat3x3<int> int3x3_t, imat3x3_t, mat3x3i_t;
		typedef Mat4x4<int> int4x4_t, imat4x4_t, mat4x4i_t;

		typedef Mat2x2<short> short2x2_t, hmat2x2_t, mat2x2h_t;
		typedef Mat3x3<short> short3x3_t, hmat3x3_t, mat3x3h_t;
		typedef Mat4x4<short> short4x4_t, hmat4x4_t, mat4x4h_t;

		/** The element tpye of the matrix. */
		template<class T>
		/** Represents a 2x2 matrix. The values are stored column-wise. */
		struct Mat2x2
		{
			/** Converts a 2x2 matrix of one type to another. */
			template<class U>
			explicit Mat2x2<T>(Mat2x2<U> const& m);

			/** Constructs a 2x2 matrix. The values are passed row-wise. */
			Mat2x2(T const& v00, T const& v10, T const& v01, T const& v11);

			/** Constructs a 2x2 matrix with the given columns.
			@param[in] v0:
				the first column of the matrix.
			@param[in] v1:
				the second column of the matrix. */
			Mat2x2(Vec2<T> const& v0, Vec2<T> const& v1);


			Mat2x2<T> operator*(Mat2x2<T> const& rval) const;
			Vec2<T> operator*(Vec2<T> const& rval) const;

			bool operator==(Mat2x2<T> const& other) const;
			bool operator!=(Mat2x2<T> const& other) const;

			static const Mat2x2<T> kIdentity;

			/** The columns of the matrix. */
			Vec2<T> v0, v1;
		};

		template<class T>
		Mat2x2<T> operator*(float a, Mat2x2<T> const& b);

		/** The element type of the matrix. */
		template<class T>
		/** Represents a 3x3 matrix. The values are stored column-wise. */
		struct Mat3x3
		{
			/** Converts a 3x3 matrix of one type to another. */
			template<class U>
			explicit Mat3x3<T>(Mat3x3<U> const& m);

			/** Constructs a 3x3 matrix. The values are passed row-wise. */
			Mat3x3(T const& v00, T const& v10, T const& v20,
				T const& v01, T const& v11, T const& v21,
				T const& v02, T const& v12, T const& v22);

			/** Constructs a 3x3 matrix with the given columns.
			@param[in] v0:
				the first column of the matrix.
			@param[in] v1:
				the second column of the matrix.
			@param[in] v2:
				the third column of the matrix. */
			Mat3x3(Vec3<T> const& v0, Vec3<T> const& v1, Vec3<T> const& v2);

			Mat3x3<T> operator*(Mat3x3<T> const& rval) const;
			Vec3<T> operator*(Vec3<T> const& rval) const;

			bool operator==(Mat3x3<T> const& other) const;
			bool operator!=(Mat3x3<T> const& other) const;

			static const Mat3x3<T> kIdentity;

			/** The columns of the matrix. */
			Vec3<T> v0, v1, v2;
		};

		template<class T>
		Mat3x3<T> operator*(float a, Mat3x3<T> const& b);

		/** The element type of the matrix. */
		template<class T>
		/** Represents a 4x4 matrix. The values are stored column-wise. */
		struct Mat4x4
		{
			/** Converts a 4x4 matrix of one type to another. */
			template<class U>
			explicit Mat4x4(Mat4x4<U> const& m);

			/** Constructs a 4x4 matrix. The values are passed row-wise. */
			Mat4x4(
				T v00, T v10, T v20, T v30,
				T v01, T v11, T v21, T v31,
				T v02, T v12, T v22, T v32,
				T v03, T v13, T v23, T v33);

			/** Constructs a 4x4 matrix with the given columns.
			@param[in] v0:
				the first column of the matrix.
			@param[in] v1:
				the second column of the matrix.
			@param[in] v2:
				the third column of the matrix.
			@param[in] v3:
				the fourth column of the matrix. */
			Mat4x4(Vec4<T> const& v0, Vec4<T> const& v1, Vec4<T> const& v2, Vec4<T> const& v3);

			Mat4x4<T> operator*(Mat4x4<T> const& rval) const;
			Vec4<T> operator*(Vec4<T> const& rval) const;
			Ray<T> operator*(Ray<T> const& val) const;

			bool operator==(Mat4x4<T> const& other) const;
			bool operator!=(Mat4x4<T> const& other) const;

			static Mat4x4<T> transform(Vec3<T> const& xAxis, Vec3<T> const& yAxis, Vec3<T> const& zAxis, Vec3<T> const& translate);
			static Mat4x4<T> look_at(Vec3<T> const& pos, Vec3<T> const& forward, Vec3<T> const& up);
			static Mat4x4<T> rotation_x(Angle const& alpha);
			static Mat4x4<T> rotation_y(Angle const& alpha);
			static Mat4x4<T> rotation_z(Angle const& alpha);
			static Mat4x4<T> translation(Vec3<T> const& delta);
			static Mat4x4<T> ortho(T width, T height, T zNear, T zFar);
			static Mat4x4<T> ortho(T xmin, T ymin, T xmax, T ymax, T zNear, T zFar);
			static Mat4x4<T> ortho_infinite(T width, T height);
			static Mat4x4<T> ortho_infinite(T xmin, T ymin, T xmax, T ymax);
			static Mat4x4<T> perspective(Angle const& yFov, T width, T height, T zNear, T zFar);
			static Mat4x4<T> rotation(Vec3<Angle> const& rotation);
			static Mat4x4<T> scaling(Vec3<T> const& scaling);
			static Mat4x4<T> transformation(Vec3<T> const& position, Vec3<Angle> const& rotation, Vec3<T> const& scaling);
			/** Kind of hacky, but works. Also, does not use inverse matrix method. maybe inverse is faster but idk. */
			static Mat4x4<T> inverse_look_at(Mat4x4<T> const& look_at);

			static const Mat4x4<T> kIdentity;

			/** The columns of the matrix. */
			Vec4<T> v0, v1, v2, v3;
		};

		template<class T>
		Mat4x4<T> operator*(float a, Mat4x4<T> const& b);
	}
}

#pragma region Implementation
namespace re
{
	namespace math
	{
		template<class T>
		const Mat2x2<T> Mat2x2<T>::kIdentity = Mat2x2<T>(1,0,0,1);

		template<class T>
		const Mat3x3<T> Mat3x3<T>::kIdentity = Mat3x3<T>(1,0,0,0,1,0,0,0,1);

		template<class T>
		const Mat4x4<T> Mat4x4<T>::kIdentity = Mat4x4<T>(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

		template<class T>
		template<class U>
		Mat2x2<T>::Mat2x2(Mat2x2<U> const& m) : v0(m.v0), v1(m.v1)	{	}

		template<class T>
		Mat2x2<T>::Mat2x2(T const& v00, T const& v10, T const& v01, T const& v11): v0(v00, v01), v1(v10, v11)	{	}

		template<class T>
		Mat2x2<T>::Mat2x2(Vec2<T> const& v0, Vec2<T> const& v1) : v0(v0), v1(v1)	{	}


		template<class T>
		template<class U>
		Mat3x3<T>::Mat3x3(Mat3x3<U> const& m) : v0(m.v0), v1(m.v1), v2(m.v2)	{	}

		template<class T>
		Mat3x3<T>::Mat3x3(T const& v00, T const& v10, T const& v20,
			T const& v01, T const& v11, T const& v21,
			T const& v02, T const& v12, T const& v22): v0(v00, v01, v02), v1(v10, v11, v12), v2(v20, v21, v22)	{	}

		template<class T>
		Mat3x3<T>::Mat3x3(Vec3<T> const& v0, Vec3<T> const& v1, Vec3<T> const& v2) : v0(v0), v1(v1), v2(v2)	{	}

		template<class T>
		template<class U>
		Mat4x4<T>::Mat4x4(Mat4x4<U> const& m): v0(m.v0), v1(m.v1), v2(m.v2), v3(m.v3)	{	}

		template<class T>
		Mat4x4<T>::Mat4x4(
			T v00, T v10, T v20, T v30,
			T v01, T v11, T v21, T v31,
			T v02, T v12, T v22, T v32,
			T v03, T v13, T v23, T v33):
			v0(v00, v01, v02, v03),
			v1(v10, v11, v12, v13),
			v2(v20, v21, v22, v23),
			v3(v30, v31, v32, v33)
		{
		}

		template<class T>
		Mat4x4<T>::Mat4x4(Vec4<T> const& v0, Vec4<T> const& v1, Vec4<T> const& v2, Vec4<T> const& v3): v0(v0), v1(v1), v2(v2), v3(v3)	{	}

		template<class T>
		Mat2x2<T> Mat2x2<T>::operator*(Mat2x2<T> const& rval) const
		{
			Vec2<T> r0(v0.x, v1.x),
					r1(v0.y, v1.y);

			return Mat2x2<T>(dot(r0, rval.v0), dot(r0, rval.v1),
							 dot(r1, rval.v0), dot(r1, rval.v1));
		}

		template<class T>
		Mat3x3<T> Mat3x3<T>::operator*(Mat3x3<T> const& rval) const
		{
			Vec3<T> r0(v0.x, v1.x, v2.x),
					r1(v0.y, v1.y, v2.y),
					r2(v0.z, v1.z, v2.z);
			return Mat3x3<T>(dot(r0, rval.v0), dot(r0, rval.v1), dot(r0, rval.v2),
							 dot(r1, rval.v0), dot(r1, rval.v1), dot(r1, rval.v2),
							 dot(r2, rval.v0), dot(r2, rval.v1), dot(r2, rval.v2));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::operator*(Mat4x4<T> const& rval) const
		{
			Vec4<T> r0(v0.x, v1.x, v2.x, v3.x),
					r1(v0.y, v1.y, v2.y, v3.y),
					r2(v0.z, v1.z, v2.z, v3.z),
					r3(v0.w, v1.w, v2.w, v3.w);
			return Mat4x4<T>(dot(r0, rval.v0), dot(r0, rval.v1), dot(r0, rval.v2), dot(r0, rval.v3),
							 dot(r1, rval.v0), dot(r1, rval.v1), dot(r1, rval.v2), dot(r1, rval.v3),
							 dot(r2, rval.v0), dot(r2, rval.v1), dot(r2, rval.v2), dot(r2, rval.v3),
							 dot(r3, rval.v0), dot(r3, rval.v1), dot(r3, rval.v2), dot(r3, rval.v3));
		}

		template<class T>
		Vec2<T> Mat2x2<T>::operator*(Vec2<T> const& rval) const
		{
			Vec2<T> r0(v0.x, v1.x),
					r1(v0.y, v1.y);
			return Vec2<T>(dot(r0, rval),
						   dot(r1, rval));
		}
		template<class T>
		Vec3<T> Mat3x3<T>::operator*(Vec3<T> const& rval) const
		{
			Vec3<T> r0(v0.x, v1.x, v2.x),
					r1(v0.y, v1.y, v2.y),
					r2(v0.z, v1.z, v2.z);
			return Vec3<T>(dot(r0,rval),
						   dot(r1,rval),
						   dot(r2,rval));
		}
		template<class T>
		Vec4<T> Mat4x4<T>::operator*(Vec4<T> const& rval) const
		{
			Vec4<T> r0(v0.x, v1.x, v2.x, v3.x),
					r1(v0.y, v1.y, v2.y, v3.y),
					r2(v0.z, v1.z, v2.z, v3.z),
					r3(v0.w, v1.w, v2.w, v3.w);
			return Vec4<T>(dot(r0,rval),
						   dot(r1,rval),
						   dot(r2,rval),
						   dot(r3,rval));
		}

		template<class T>
		Ray<T> Mat4x4<T>::operator*(Ray<T> const& rval) const
		{
			return Ray<T>(Vec3<T>(operator*(Vec4<T>(rval.position,1))), Vec3<T>(operator*(Vec4<T>(rval.direction,0))));
		}

		template<class T>
		Mat2x2<T> operator*(float a, Mat2x2<T> const& b)
		{
			return Mat2x2<T>(a*b.v0, a*b.v1);
		}
		template<class T>
		Mat3x3<T> operator*(float a, Mat3x3<T> const& b)
		{
			return Mat3x3<T>(a*b.v0, a*b.v1, a*b.v2);
		}
		template<class T>
		Mat4x4<T> operator*(float a, Mat4x4<T> const& b)
		{
			return Mat4x4<T>(a*b.v0, a*b.v1, a*b.v2, a*b.v3);
		}


		template<class T>
		bool Mat2x2<T>::operator==(Mat2x2<T> const& other) const
		{
			return v0 == other.v0 && v1 == other.v1;
		}
		template<class T>
		bool Mat3x3<T>::operator==(Mat3x3<T> const& other) const
		{
			return v0 == other.v0 && v1 == other.v1 && v2 == other.v2;
		}
		template<class T>
		bool Mat4x4<T>::operator==(Mat4x4<T> const& other) const
		{
			return v0 == other.v0 && v1 == other.v1 && v2 == other.v2 && v3 == other.v3;
		}

		template<class T>
		bool Mat2x2<T>::operator!=(Mat2x2<T> const& other) const
		{
			return v0 != other.v0 || v1 != other.v1;
		}
		template<class T>
		bool Mat3x3<T>::operator!=(Mat3x3<T> const& other) const
		{
			return v0 != other.v0 || v1 != other.v1 || v2 != other.v2;
		}
		template<class T>
		bool Mat4x4<T>::operator!=(Mat4x4<T> const& other) const
		{
			return v0 != other.v0 || v1 != other.v1 || v2 != other.v2 || v3 != other.v3;
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::transform(Vec3<T> const& xAxis, Vec3<T> const& yAxis, Vec3<T> const& zAxis, Vec3<T> const& translate)
		{
			Vec4<T> v0(xAxis, 0),
				v1 (yAxis, 0),
				v2 (zAxis, 0),
				v3 (translate, 1);
			return Mat4x4<T>(v0, v1, v2, v3);
		}
		template<class T>
                Mat4x4<T> Mat4x4<T>::look_at(Vec3<T> const& position, Vec3<T> const& forward, Vec3<T> const& up)
		{
			/** Vec3<T> _z(norm(forward));
			Vec3<T> _x(norm(cross(up,forward)));
			Vec3<T> _y(norm(cross(forward, _x)));
			Vec4<T> x(_z.x, _z.y, _z.z, -dot(_x,position));
			return Mat4x4<T>(_x.x, _y.x, _z.x, -dot(_x,position),
							 _x.y, _y.y, _z.y, -dot(_y,position),
							 _x.z, _y.z, _z.z, -dot(_z,position),
							 0, 0, 0, 1). */
			Vec3<T> _z(norm(forward));
			Vec3<T> _x(norm(cross(up,_z)));
			Vec3<T> _y(norm(cross(_z,_x)));
			return Mat4x4<T>(Vec4<T>(_x.x, _y.x, _z.x, 0),
							 Vec4<T>(_x.y, _y.y, _z.y, 0),
							 Vec4<T>(_x.z, _y.z, _z.z, 0),
							 Vec4<T>(-dot(_x, position), -dot(_y, position), -dot(_z, position), 1));
		}

		template<class T>
                Mat4x4<T> Mat4x4<T>::rotation_x(Angle const& alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return Mat4x4<T>(1, 0, 0, 0,
							 0, c,-s, 0,
							 0, s, c, 0,
							 0, 0, 0, 1);
		}
		template<class T>
                Mat4x4<T> Mat4x4<T>::rotation_y(Angle const& alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return Mat4x4<T>(c, 0, s, 0,
							 0, 1, 0, 0,
							 -s,0, c, 0,
							 0, 0, 0, 1);
		}
		template<class T>
                Mat4x4<T> Mat4x4<T>::rotation_z(Angle const& alpha)
		{
			T c = cos(alpha);
			T s = sin(alpha);
			return Mat4x4<T>(c,-s, 0, 0,
							 s, c, 0, 0,
							 0, 0, 1, 0,
							 0, 0, 0, 1);
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::translation(Vec3<T> const& delta)
		{
			return Mat4x4<T>(1, 0, 0, delta.x,
							 0, 1, 0, delta.y,
							 0, 0, 1, delta.z,
							 0, 0,	0, 1);
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::ortho(T width, T height, T zNear, T zFar)
		{
			T inv = T(-1)/(zFar-zNear);
			return Mat4x4<T>(
				Vec4<T>(1/width, 0, 0, 0),
				Vec4<T>(0, 1/height, 0, 0),
				Vec4<T>(0, 0, inv+inv, (zFar+zNear)*inv),
				Vec4<T>(0, 0, 0, 1));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::ortho(T xmin, T ymin, T xmax, T ymax, T zNear, T zFar)
		{
			T w = (xmax-xmin)/2;
			T h = (ymax-ymin)/2;
			return ortho(w, h, zNear, zFar)*translation(Vec3<T>(-xmin-w, -ymin+h, 0));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::ortho_infinite(T width, T height)
		{
			return Mat4x4<T>(
				Vec4<T>(1/width, 0, 0, 0),
				Vec4<T>(0, 1/height, 0, 0),
				Vec4<T>(0, 0, 0, 0),
				Vec4<T>(0, 0, 0, 1));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::ortho_infinite(T xmin, T ymin, T xmax, T ymax)
		{
			return ortho_infinite((xmax-xmin)/2, (ymax-ymin)/2) * translation(Vec3<T>(-xmin,-ymin,0));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::perspective(Angle const& yFov, T width, T height, T zNear, T zFar)
		{
			/** T inv = T(1)/(zNear-zFar);
			T t = (zNear*zFar)*inv;
			T _tan = T(1)/tan(yFov/T(2));
			T aspect = height / width;
			T xFov = _tan * aspect;

			return Mat4x4<T>(xFov, 0,    0,                0,
							 0,    _tan, 0,                0,
							 0,    0,    (zFar+zNear)*inv, T(2)*(zNear*zFar)*inv,
							 0,    0,    1,                0). */

			/** const T ar = height / width;
			const T tanHalfFOV = T(1)/tan(yFov/T(2));
			const T zRange = T(1)/(zNear - zFar);

			return Mat4x4<T>(
				Vec4<T>(ar*tanHalfFOV, T(0), T(0), T(0)),
				Vec4<T>(T(0), tanHalfFOV, T(0), T(0)),
				Vec4<T>(T(0), T(0), T(-zNear-zFar)*zRange, T(2)*zFar*zNear*zRange),
				Vec4<T>(T(0), T(0), T(1), T(0))). */

			const T _tan = T(1)/tan(rad(yFov.rad() * T(0.5)));
			const T AR = height / width;
			const T A = AR * _tan;
			T const& B = _tan;
			const T C = zFar / (zFar-zNear);
			const T D = T(1);
			const T E = -zNear * C;

			return Mat4x4<T>(
				Vec4<T>(A,0,0,0),
				Vec4<T>(0,B,0,0),
				Vec4<T>(0,0,C,D),
				Vec4<T>(0,0,E,0));
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::rotation(Vec3<Angle> const& axis)
		{
                        return rotation_x(axis.z)*rotation_y(axis.y)*rotation_z(axis.x);
		}


		template<class T>
		Mat4x4<T> Mat4x4<T>::scaling(Vec3<T> const& scaling)
		{
			return Mat4x4<T>(scaling.x,0,0,0,
							 0,scaling.y,0,0,
							 0,0,scaling.z,0,
							 0,0,0,1);
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::transformation(Vec3<T> const& position, Vec3<Angle> const& rotation, Vec3<T> const& scaling)
		{
			return translation(position) * Mat4x4<T>::rotation(rotation) * Mat4x4<T>::scaling(scaling);
		}

		template<class T>
		Mat4x4<T> Mat4x4<T>::inverse_look_at(Mat4x4<T> const& look_at)
		{
			const math::fvec3_t origin = math::fvec3_t(look_at * math::fvec4_t(0,0,0,1));
			const math::fvec3_t up = math::fvec3_t(look_at * math::fvec4_t(0,1,0,1)) - origin;
			const math::fvec3_t forward = math::fvec3_t(look_at * math::fvec4_t(0,0,1,1)) - origin;

			const math::fmat4x4_t inv_view = math::fmat4x4_t::look_at(origin, forward, up);
			return inv_view;
		}
	}
}

#pragma endregion

#endif

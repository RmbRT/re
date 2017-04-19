#ifndef __re_camera_hpp_defined
#define __re_camera_hpp_defined

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "defines.hpp"
#include "types.hpp"

namespace re
{

	enum class CameraType
	{
		LookAt,
		Directional,
		Following
	};

	class LookAtCamera;
	class DirectionalCamera;
	class FollowingCamera;
	struct CameraBase;
	class Camera;

	struct CameraBase
	{
		math::fvec3_t a,b,c;
		CameraBase(math::fvec3_t const& a, math::fvec3_t const& b, math::fvec3_t const& c);
	};
	class Camera
	{
		CameraType m_type;
		CameraBase m_base;
	public:
		Camera(LookAtCamera const& lookat);
		Camera(DirectionalCamera const& directional);
		Camera(FollowingCamera const& following);

		math::fmat4x4_t view_matrix() const;
		CameraType type() const;

		template<CameraType type>
		void convert();

		LookAtCamera * look_at();
		const LookAtCamera * look_at() const;
		DirectionalCamera * directional();
		const DirectionalCamera * directional() const;
		FollowingCamera * following();
		const FollowingCamera * following() const;

	};

	class LookAtCamera: public CameraBase
	{
	public:
		LookAtCamera(math::fvec3_t const& position, math::fvec3_t const& target, math::fvec3_t const& up = math::fvec3_t(0,1,0));

		void set_position(
			math::fvec3_t const& position);
		void set_target(math::fvec3_t const& target);
		void set_up(math::fvec3_t const& up);

		math::fvec3_t const& position() const;
		math::fvec3_t const& target() const;
		math::fvec3_t const& up() const;

		math::fmat4x4_t view_matrix() const;
	};

	class DirectionalCamera: public CameraBase
	{
	public:
		DirectionalCamera(math::fvec3_t const& position, math::fvec3_t const& direction, math::fvec3_t const& up = math::fvec3_t(0,1,0));

		void set_position(math::fvec3_t const& position);
		void set_direction(math::fvec3_t const& direction);
		void set_up(math::fvec3_t const& up);

		math::fvec3_t const& position() const;
		math::fvec3_t const& direction() const;
		math::fvec3_t const& up() const;

		math::fmat4x4_t view_matrix() const;
	};

	class FollowingCamera: public CameraBase
	{
	public:
		FollowingCamera(math::fvec3_t const& target, math::fvec3_t const& distance, math::fvec3_t const& up = math::fvec3_t(0,1,0));

		void set_target(math::fvec3_t const& position);
		void set_distance(math::fvec3_t const& distance);
		void set_up(math::fvec3_t const& up);

		math::fvec3_t const& target() const;
		math::fvec3_t const& distance() const;
		math::fvec3_t const& up() const;

		math::fmat4x4_t view_matrix() const;
	};
}

#endif
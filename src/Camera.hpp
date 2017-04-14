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
		CameraBase(const math::fvec3_t &a, const math::fvec3_t &b, const math::fvec3_t &c);
	};
	class Camera
	{
		CameraType type;
		CameraBase base;
	public:
		Camera(const LookAtCamera &lookat);
		Camera(const DirectionalCamera &directional);
		Camera(const FollowingCamera &following);

		math::fmat4x4_t getViewMatrix() const;
		CameraType getType() const;

		template<CameraType type>
		void convert();

		LookAtCamera * getLookAt();
		const LookAtCamera * getLookAt() const;
		DirectionalCamera * getDirectional();
		const DirectionalCamera * getDirectional() const;
		FollowingCamera * getFollowing();
		const FollowingCamera * getFollowing() const;

	};

	class LookAtCamera: public CameraBase
	{
	public:
		LookAtCamera(const math::fvec3_t &position, const math::fvec3_t &target, const math::fvec3_t &up = math::fvec3_t(0,1,0));

		void setPosition(const math::fvec3_t &position);
		void setTarget(const math::fvec3_t &target);
		void setUp(const math::fvec3_t &up);

		const math::fvec3_t &getPosition() const;
		const math::fvec3_t &getTarget() const;
		const math::fvec3_t &getUp() const;

		math::fmat4x4_t getViewMatrix() const;
	};

	class DirectionalCamera: public CameraBase
	{
	public:
		DirectionalCamera(const math::fvec3_t &position, const math::fvec3_t &direction, const math::fvec3_t &up = math::fvec3_t(0,1,0));

		void setPosition(const math::fvec3_t &position);
		void setDirection(const math::fvec3_t &direction);
		void setUp(const math::fvec3_t &up);

		const math::fvec3_t &getPosition() const;
		const math::fvec3_t &getDirection() const;
		const math::fvec3_t &getUp() const;

		math::fmat4x4_t getViewMatrix() const;
	};

	class FollowingCamera: public CameraBase
	{
	public:
		FollowingCamera(const math::fvec3_t &target, const math::fvec3_t &distance, const math::fvec3_t &up = math::fvec3_t(0,1,0));

		void setTarget(const math::fvec3_t &position);
		void setDistance(const math::fvec3_t &distance);
		void setUp(const math::fvec3_t &up);

		const math::fvec3_t &getTarget() const;
		const math::fvec3_t &getDistance() const;
		const math::fvec3_t &getUp() const;

		math::fmat4x4_t getViewMatrix() const;
	};
}

#endif
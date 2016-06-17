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
		math::fvec3 a,b,c;
		CameraBase(const math::fvec3 &a, const math::fvec3 &b, const math::fvec3 &c);
	};
	class Camera
	{
		CameraType type;
		CameraBase base;
	public:
		Camera(const LookAtCamera &lookat);
		Camera(const DirectionalCamera &directional);
		Camera(const FollowingCamera &following);

		math::fmat4x4 getViewMatrix() const;
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
		LookAtCamera(const math::fvec3 &position, const math::fvec3 &target, const math::fvec3 &up = math::fvec3(0,1,0));
			
		void setPosition(const math::fvec3 &position);
		void setTarget(const math::fvec3 &target);
		void setUp(const math::fvec3 &up);

		const math::fvec3 &getPosition() const;
		const math::fvec3 &getTarget() const;
		const math::fvec3 &getUp() const;

		math::fmat4x4 getViewMatrix() const;
	};

	class DirectionalCamera: public CameraBase
	{
	public:
		DirectionalCamera(const math::fvec3 &position, const math::fvec3 &direction, const math::fvec3 &up = math::fvec3(0,1,0));

		void setPosition(const math::fvec3 &position);
		void setDirection(const math::fvec3 &direction);
		void setUp(const math::fvec3 &up);

		const math::fvec3 &getPosition() const;
		const math::fvec3 &getDirection() const;
		const math::fvec3 &getUp() const;

		math::fmat4x4 getViewMatrix() const;
	};
		
	class FollowingCamera: public CameraBase
	{
	public:
		FollowingCamera(const math::fvec3 &target, const math::fvec3 &distance, const math::fvec3 &up = math::fvec3(0,1,0));

		void setTarget(const math::fvec3 &position);
		void setDistance(const math::fvec3 &distance);
		void setUp(const math::fvec3 &up);

		const math::fvec3 &getTarget() const;
		const math::fvec3 &getDistance() const;
		const math::fvec3 &getUp() const;

		math::fmat4x4 getViewMatrix() const;
	};
}

#endif
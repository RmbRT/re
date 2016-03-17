#include "Camera.hpp"

#define LookAtCameraPosition a
#define LookAtCameraTarget b
#define LookAtCameraUp c

#define DirectionalCameraPosition a
#define DirectionalCameraDirection b
#define DirectionalCameraUp c

#define FollowingCameraTarget a
#define FollowingCameraDistance b
#define FollowingCameraUp c

namespace re
{
	LookAtCamera::LookAtCamera(const math::fvec3 &position, const math::fvec3 &target, const math::fvec3 &up): CameraBase(position, target, up)	{	}
	void LookAtCamera::setPosition(const math::fvec3 &position)
	{
		this->LookAtCameraPosition= position;
	}
	void LookAtCamera::setTarget(const math::fvec3 &target)
	{
		this->LookAtCameraTarget= target;
	}
	void LookAtCamera::setUp(const math::fvec3 &up)
	{
		this->LookAtCameraUp = up;
	}
	const math::fvec3 &LookAtCamera::getPosition() const
	{
		return LookAtCameraPosition;
	}
	const math::fvec3 &LookAtCamera::getTarget() const
	{
		return LookAtCameraTarget;
	}
	const math::fvec3 &LookAtCamera::getUp() const
	{
		return LookAtCameraUp;
	}
	math::fmat4x4 LookAtCamera::getViewMatrix() const
	{
		return math::fmat4x4::lookAt(LookAtCameraPosition, LookAtCameraTarget-LookAtCameraPosition, LookAtCameraUp);
	}


	DirectionalCamera::DirectionalCamera(const math::fvec3 &position, const math::fvec3 &direction, const math::fvec3 &up): CameraBase(position, direction, up)	{	}

	void DirectionalCamera::setPosition(const math::fvec3 &position)
	{
		this->DirectionalCameraPosition = position;
	}
	void DirectionalCamera::setDirection(const math::fvec3 &direction)
	{
		this->DirectionalCameraDirection = direction;
	}
	void DirectionalCamera::setUp(const math::fvec3 &up)
	{
		this->DirectionalCameraUp = up;
	}

	const math::fvec3 &DirectionalCamera::getPosition() const
	{
		return DirectionalCameraPosition;
	}
	const math::fvec3 &DirectionalCamera::getDirection() const
	{
		return DirectionalCameraDirection;
	}
	const math::fvec3 &DirectionalCamera::getUp() const
	{
		return DirectionalCameraUp;
	}
	math::fmat4x4 DirectionalCamera::getViewMatrix() const
	{
		return math::fmat4x4::lookAt(DirectionalCameraPosition, DirectionalCameraDirection, DirectionalCameraUp);
	}

	FollowingCamera::FollowingCamera(const math::fvec3 &target, const math::fvec3 &distance, const math::fvec3 &up): CameraBase(target, distance, up)	{	}

	void FollowingCamera::setTarget(const math::fvec3 &target)
	{
		this->FollowingCameraTarget = target;
	}
	void FollowingCamera::setDistance(const math::fvec3 &distance)
	{
		this->FollowingCameraDistance = distance;
	}
	void FollowingCamera::setUp(const math::fvec3 &up)
	{
		this->FollowingCameraUp = up;
	}
		
	const math::fvec3 &FollowingCamera::getTarget() const
	{
		return FollowingCameraTarget;
	}
	const math::fvec3 &FollowingCamera::getDistance() const
	{
		return FollowingCameraDistance;
	}
	const math::fvec3 &FollowingCamera::getUp() const
	{
		return FollowingCameraUp;
	}

	math::fmat4x4 FollowingCamera::getViewMatrix() const
	{
		return math::fmat4x4::lookAt(FollowingCameraTarget-FollowingCameraDistance, FollowingCameraDistance, FollowingCameraUp);
	}


	
	Camera::Camera(const LookAtCamera &lookat) : type(CameraType::LookAt), base(lookat) {}
	Camera::Camera(const DirectionalCamera &directional) : type(CameraType::Directional), base(directional) {}
	Camera::Camera(const FollowingCamera &following): type(CameraType::Following), base(following) {}
	math::fmat4x4 Camera::getViewMatrix() const
	{
		switch(type)
		{
		case CameraType::LookAt: return reinterpret<const LookAtCamera>(base)->getViewMatrix();
		case CameraType::Directional: return reinterpret<const DirectionalCamera>(base)->getViewMatrix();
		case CameraType::Following: return reinterpret<const FollowingCamera>(base)->getViewMatrix();
		default:
			RE_ASSERTION_FAILURE("INVALID ENUM");
		}
	}
	CameraType Camera::getType() const
	{
		return type;
	}
	template<CameraType type>
	void Camera::convert()
	{
		switch(this->type)
		{
		case CameraType::Directional:
			{
				switch(type)
				{
				case CameraType::Directional:
					return;
				case CameraType::Following:
					{
						base = FollowingCamera(base.DirectionalCameraPosition+base.DirectionalCameraDirection, base.DirectionalCameraDirection, base.DirectionalCameraUp);
						return;
					} break;
				case CameraType::LookAt:
					{
						base = LookAtCamera(base.DirectionalCameraPosition, base.DirectionalCameraPosition+base.DirectionalCameraDirection, base.DirectionalCameraUp);
						return;
					} break;
				}
			} break;
		case CameraType::Following:
			{
				switch(type)
				{
				case CameraType::Directional:
					{
						base = DirectionalCamera(base.FollowingCameraTarget-base.FollowingCameraDistance, base.FollowingCameraDistance, base.FollowingCameraUp);
						return;
					}
				case CameraType::Following:
						return;
				case CameraType::LookAt:
					{
						base = LookAtCamera(base.FollowingCameraTarget-base.FollowingCameraDistance, base.FollowingCameraTarget, base.FollowingCameraUp);
						return;
					} break;
				}
			} break;
		case CameraType::LookAt:
			{
				switch(type)
				{
				case CameraType::Directional:
					{
						base = DirectionalCamera(base.LookAtCameraPosition, base.LookAtCameraTarget-base.LookAtCameraPosition, base.LookAtCameraUp);
						return;
					}
				case CameraType::Following:
					{
						base = FollowingCamera(base.LookAtCameraTarget, base.LookAtCameraTarget-base.LookAtCameraPosition, base.LookAtCameraUp);
						return;
					} break;
				case CameraType::LookAt:
						return;
				}
			} break;
		}
	}
	unsafe<LookAtCamera> Camera::getLookAt()
	{
		if(type == CameraType::LookAt)
			return base;
		else return nullptr;
	}
	unsafe<const LookAtCamera> Camera::getLookAt() const
	{
		if(type == CameraType::LookAt)
			return base;
		else return nullptr;
	}
	unsafe<DirectionalCamera> Camera::getDirectional()
	{
		if(type == CameraType::Directional)
			return base;
		else return nullptr;
	}
	unsafe<const DirectionalCamera> Camera::getDirectional() const
	{
		if(type == CameraType::Directional)
			return base;
		else return nullptr;
	}
	unsafe<FollowingCamera> Camera::getFollowing()
	{
		if(type == CameraType::Following)
			return base;
		else return nullptr;
	}
	unsafe<const FollowingCamera> Camera::getFollowing() const
	{
		if(type == CameraType::Following)
			return base;
		else return nullptr;
	}
	CameraBase::CameraBase(const math::fvec3 &a, const math::fvec3 &b, const math::fvec3 &c): a(a),b(b),c(c) {}
}
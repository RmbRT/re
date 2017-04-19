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
	LookAtCamera::LookAtCamera(
		math::fvec3_t const& position,
		math::fvec3_t const& target,
		math::fvec3_t const& up):
		CameraBase(position, target, up)
	{
	}

	void LookAtCamera::set_position(
		math::fvec3_t const& position)
	{
		this->LookAtCameraPosition= position;
	}
	void LookAtCamera::set_target(
		math::fvec3_t const& target)
	{
		this->LookAtCameraTarget= target;
	}
	void LookAtCamera::set_up(
		math::fvec3_t const& up)
	{
		this->LookAtCameraUp = up;
	}

	math::fvec3_t const& LookAtCamera::position() const
	{
		return LookAtCameraPosition;
	}
	math::fvec3_t const& LookAtCamera::target() const
	{
		return LookAtCameraTarget;
	}
	math::fvec3_t const& LookAtCamera::up() const
	{
		return LookAtCameraUp;
	}
	math::fmat4x4_t LookAtCamera::view_matrix() const
	{
		return math::fmat4x4_t::look_at(
			LookAtCameraPosition,
			LookAtCameraTarget-LookAtCameraPosition,
			LookAtCameraUp);
	}


	DirectionalCamera::DirectionalCamera(
		math::fvec3_t const& position,
		math::fvec3_t const& direction,
		math::fvec3_t const& up):
		CameraBase(position, direction, up)
	{
	}

	void DirectionalCamera::set_position(
		math::fvec3_t const& position)
	{
		this->DirectionalCameraPosition = position;
	}
	void DirectionalCamera::set_direction(
		math::fvec3_t const& direction)
	{
		this->DirectionalCameraDirection = direction;
	}
	void DirectionalCamera::set_up(
		math::fvec3_t const& up)
	{
		this->DirectionalCameraUp = up;
	}

	math::fvec3_t const& DirectionalCamera::position() const
	{
		return DirectionalCameraPosition;
	}
	math::fvec3_t const& DirectionalCamera::direction() const
	{
		return DirectionalCameraDirection;
	}
	math::fvec3_t const& DirectionalCamera::up() const
	{
		return DirectionalCameraUp;
	}
	math::fmat4x4_t DirectionalCamera::view_matrix() const
	{
		return math::fmat4x4_t::look_at(
			DirectionalCameraPosition,
			DirectionalCameraDirection,
			DirectionalCameraUp);
	}

	FollowingCamera::FollowingCamera(
		math::fvec3_t const& target,
		math::fvec3_t const& distance,
		math::fvec3_t const& up):
		CameraBase(target, distance, up)
	{
	}

	void FollowingCamera::set_target(
		math::fvec3_t const& target)
	{
		this->FollowingCameraTarget = target;
	}
	void FollowingCamera::set_distance(
		math::fvec3_t const& distance)
	{
		this->FollowingCameraDistance = distance;
	}
	void FollowingCamera::set_up(
		math::fvec3_t const& up)
	{
		this->FollowingCameraUp = up;
	}

	math::fvec3_t const& FollowingCamera::target() const
	{
		return FollowingCameraTarget;
	}
	math::fvec3_t const& FollowingCamera::distance() const
	{
		return FollowingCameraDistance;
	}
	math::fvec3_t const& FollowingCamera::up() const
	{
		return FollowingCameraUp;
	}

	math::fmat4x4_t FollowingCamera::view_matrix() const
	{
		return math::fmat4x4_t::look_at(
			FollowingCameraTarget-FollowingCameraDistance,
			FollowingCameraDistance,
			FollowingCameraUp);
	}


	Camera::Camera(
		LookAtCamera const& lookat):
		m_type(CameraType::LookAt),
		m_base(lookat)
	{
	}

	Camera::Camera(
		DirectionalCamera const& directional):
		m_type(CameraType::Directional),
		m_base(directional)
	{
	}

	Camera::Camera(
		FollowingCamera const& following):
		m_type(CameraType::Following),
		m_base(following)
	{
	}

	math::fmat4x4_t Camera::view_matrix() const
	{
		switch(m_type)
		{
		case CameraType::LookAt: return reinterpret_cast<LookAtCamera const&>(m_base).view_matrix();
		case CameraType::Directional: return reinterpret_cast<DirectionalCamera const&>(m_base).view_matrix();
		case CameraType::Following: return reinterpret_cast<FollowingCamera const&>(m_base).view_matrix();
		default:
			RE_ASSERTION_FAILURE("INVALID ENUM");
		}
	}
	CameraType Camera::type() const
	{
		return m_type;
	}
	template<CameraType m_type>
	void Camera::convert()
	{
		switch(this->m_type)
		{
		case CameraType::Directional:
			{
				switch(m_type)
				{
				case CameraType::Directional:
					return;
				case CameraType::Following:
					{
						m_base = FollowingCamera(m_base.DirectionalCameraPosition+m_base.DirectionalCameraDirection, m_base.DirectionalCameraDirection, m_base.DirectionalCameraUp);
						return;
					} break;
				case CameraType::LookAt:
					{
						m_base = LookAtCamera(m_base.DirectionalCameraPosition, m_base.DirectionalCameraPosition+m_base.DirectionalCameraDirection, m_base.DirectionalCameraUp);
						return;
					} break;
				}
			} break;
		case CameraType::Following:
			{
				switch(m_type)
				{
				case CameraType::Directional:
					{
						m_base = DirectionalCamera(m_base.FollowingCameraTarget-m_base.FollowingCameraDistance, m_base.FollowingCameraDistance, m_base.FollowingCameraUp);
						return;
					}
				case CameraType::Following:
						return;
				case CameraType::LookAt:
					{
						m_base = LookAtCamera(m_base.FollowingCameraTarget-m_base.FollowingCameraDistance, m_base.FollowingCameraTarget, m_base.FollowingCameraUp);
						return;
					} break;
				}
			} break;
		case CameraType::LookAt:
			{
				switch(m_type)
				{
				case CameraType::Directional:
					{
						m_base = DirectionalCamera(m_base.LookAtCameraPosition, m_base.LookAtCameraTarget-m_base.LookAtCameraPosition, m_base.LookAtCameraUp);
						return;
					}
				case CameraType::Following:
					{
						m_base = FollowingCamera(m_base.LookAtCameraTarget, m_base.LookAtCameraTarget-m_base.LookAtCameraPosition, m_base.LookAtCameraUp);
						return;
					} break;
				case CameraType::LookAt:
						return;
				}
			} break;
		}
	}
	LookAtCamera * Camera::look_at()
	{
		if(m_type == CameraType::LookAt)
			return static_cast<LookAtCamera *>(&m_base);
		else return nullptr;
	}
	const LookAtCamera * Camera::look_at() const
	{
		if(m_type == CameraType::LookAt)
			return static_cast<LookAtCamera const*>(&m_base);
		else return nullptr;
	}
	DirectionalCamera * Camera::directional()
	{
		if(m_type == CameraType::Directional)
			return static_cast<DirectionalCamera *>(&m_base);
		else return nullptr;
	}
	const DirectionalCamera * Camera::directional() const
	{
		if(m_type == CameraType::Directional)
			return static_cast<DirectionalCamera const*>(&m_base);
		else return nullptr;
	}
	FollowingCamera * Camera::following()
	{
		if(m_type == CameraType::Following)
			return static_cast<FollowingCamera *>(&m_base);
		else return nullptr;
	}
	const FollowingCamera * Camera::following() const
	{
		if(m_type == CameraType::Following)
			return static_cast<FollowingCamera const*>(&m_base);
		else return nullptr;
	}
	CameraBase::CameraBase(
		math::fvec3_t const& a,
		math::fvec3_t const& b,
		math::fvec3_t const& c):
		a(a),
		b(b),
		c(c)
	{
	}
}
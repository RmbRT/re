#ifndef __re_angle_hpp_defined
#define __re_angle_hpp_defined

#include "../base_types.hpp"
#include "../defines.hpp"


namespace re
{
	namespace math
	{

		const float PI_OVER_180 = (3.14159265359/180.0);
		const float PI_UNDER_180 = (180.0/3.14159265359);

		enum class AngleType
		{
			DEG,
			RAD
		};

		class Angle
		{
			float val;
			AngleType type;
		public:
			Angle(): val(0), type(AngleType::DEG) { }
			Angle(AngleType type, float val) : val(val), type(type)	{	}

			float deg() const { if(type==AngleType::RAD) return val * PI_UNDER_180; else return	val; }
			float rad() const { if(type==AngleType::DEG) return val * PI_OVER_180; else return val; }
		};

		static Angle deg(float deg)	{	return Angle(AngleType::DEG, deg);	}
		static Angle rad(float rad)	{	return Angle(AngleType::RAD, rad);	}
		static float cos(const Angle &angle)	{	return cosf(angle.rad());	}
		static float sin(const Angle &angle)	{	return sinf(angle.rad());	}
		static float tan(const Angle &angle)	{	return tanf(angle.rad());	}
		static float acos(const Angle &angle)	{	return acosf(angle.rad());	}
		static float asin(const Angle &angle)	{	return asinf(angle.rad());	}
		static float atan(const Angle &angle)	{	return atanf(angle.rad());	}
	}
}



#endif
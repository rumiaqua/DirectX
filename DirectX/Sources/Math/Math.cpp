# include "Math.hpp"

namespace Math
{
	float ToRadian(float x)
	{
		return x * Radian;
	}

	float ToDegree(float x)
	{
		return x * Degree;
	}

	float Sin(float x)
	{
		return std::sinf(x);
	}

	float Cos(float x)
	{
		return std::cosf(x);
	}

	float Tan(float x)
	{
		return std::tanf(x);
	}

	float Asin(float x)
	{
		return std::asinf(x);
	}

	float Acos(float x)
	{
		return std::acosf(x);
	}

	float Atan(float x)
	{
		return std::atanf(x);
	}

	float Atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

	float Floor(float x)
	{
		return std::floorf(x);
	}

	float Ceiling(float x)
	{
		return std::ceilf(x);
	}

	float Round(float x)
	{
		return std::roundf(x);
	}

	float Sign(float x)
	{
		return std::signbit(x) ? 1.0f : -1.0f;
	}

	float Pow(float x, float y)
	{
		return std::powf(x, y);
	}

	float Sqrt(float x)
	{
		return std::sqrtf(x);
	}

	float Saturate(float x)
	{
		return Clamp(x, 0.0f, 1.0f);
	}

	float Smooth(float x, int y)
	{
		float f = Pow(10.0f, -static_cast<float>(y));
		int i = (int)(x * f);
		return i / f;
	}

	float Clamp(float x, float y, float z)
	{
		return Min({ Max({ x, y }), z });
	}
}

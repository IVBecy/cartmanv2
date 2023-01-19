#pragma once
#include <numbers>
#include <cstdint>
#include <cmath>

constexpr float Deg2Rad(const float deg) noexcept
{
	return deg * (std::numbers::pi_v<float> / 180.f);
}

class CVector
{
public:
	constexpr CVector operator+(const CVector& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator-(const CVector& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr CVector operator*(const CVector& other) const noexcept
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	constexpr CVector operator/(const CVector& other) const noexcept
	{
		return { x / other.x, y / other.y, z / other.z };
	}

	inline CVector ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f 
		};
	}

	CVector ToVector() const noexcept
	{
		return {
			std::cos(Deg2Rad(x)) * std::cos(Deg2Rad(y)),
			std::cos(Deg2Rad(x)) * std::sin(Deg2Rad(y)),
			-std::sin(Deg2Rad(x))
		};
	}

	float x{ }, y{ }, z{ };
};

__declspec(align(16)) class CVectorAligned : public CVector
{
public:
	constexpr CVectorAligned operator-(const CVectorAligned& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	float w{ };
};

// 2D Vector
struct Vector2
{
	float x, y;
};

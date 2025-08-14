#pragma once
#include "Math.h"
#include <cassert>

namespace viper
{
	template<typename T>
	struct Vector3
	{
		union{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3() = default;
		Vector3(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z + v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z + v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z + v.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z + s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z + s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z + s); }

		Vector3& operator += (const Vector3& v) { x += v.x, y += v.y, z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x, y -= v.y, z += v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x, y *= v.y, z += v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x, y /= v.y, z += v.z; return *this; }

		Vector3& operator += (float s) { x += s, y += s, z += s; return *this; }
		Vector3& operator -= (float s) { x -= s, y -= s, z += s; return *this; }
		Vector3& operator *= (float s) { x *= s, y *= s, z += s; return *this; }
		Vector3& operator /= (float s) { x /= s, y /= s, z += s; return *this; }

		/// <summary>
		/// Calculates the squared length (magnitude) of a 3D vector.
		/// </summary>
		/// <returns>The sum of the squares of the x, y, and z components of the vector.</returns>
		float LengthSqr() const  { return (x * x) + (y * y) + (z * z); }

		/// <summary>
		/// Calculates the length (magnitude) of the vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const { return viper::math::sqrtf(LengthSqr()); }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
	{
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

	template<typename T>
	std::istream& operator>>(std::istream& os, Vector3<T>& v)
	{
		char ch = '\0';
		// { x, y, z }
		if (!(os >> std::ws >> ch) || ch != '{') {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> v.x)) {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> ch) || ch != ',') {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> v.y)) {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> ch) || ch != ',') {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> v.z)) {
			os.setstate(std::ios::failbit);
			return os;
		}
		if (!(os >> std::ws >> ch) || ch != '}') {
			os.setstate(std::ios::failbit);
			return os;
		}
		return os;
	}

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}
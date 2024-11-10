#pragma once
#include "Vector.hpp"

#define toRadians(x) x * 0.01745329251f

class AxixAngle
{
	//axis need to be a normalized vector
	const vec3 RotateVectorAroundAxisAngle(const vec3& v, const vec3& axis, const float &angle)
	{
		float a = toRadians(angle);
		float sinAngle = sin(a);
		float cosAngle = cos(a);

		return v * cosAngle + axis.cross(v) * sinAngle + axis * v.dot(axis) * (1 - cosAngle);
	}
};
#pragma once
#include "Vector.hpp"


class commonMath
{
	public:
	static const float approach(const float &goal, const float &current, const float &dt)
	{
		const float diff = goal - current;
		const bool bigger = diff > dt;
		const bool lesser = diff < -dt;
		return (bigger) * (current + dt) + (lesser) * (current - dt) + (!bigger && !lesser) * goal;
	}
	static const float remap(const float& value, const float& low1, const float& high1, const float& low2, const float& high2)
	{
		float yellow = (value - low1) / (high1 - low1);
		float green = yellow * (high2 - low2) + low2;
		return green;
	}
	// plane_normal need to be a normilaized vector
	static const bool LinePlaneIntersection(const vec3& plane_point, const vec3& plane_normal, const vec3& lineStart, const vec3& lineEnd, vec3& intersection, float &fraction)
	{ 
		vec3 v = lineEnd - lineStart;
		vec3 w = plane_point - lineStart;

		const float k = w.dot(plane_point)/v.dot(plane_point);

		intersection = lineStart + v * k;

		fraction = k;

		return k >= 0.0f && k <= 1.0f;
	}

	static const vec3 NearestPointOnSphere(const vec3 &origin, const float &r, const vec3 &point)
	{
		vec3 AM = point - origin;
		AM = AM.normalized();
		return origin + AM * r;
	}
};

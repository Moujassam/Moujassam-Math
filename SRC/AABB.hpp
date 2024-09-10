#pragma once

#include "Vector.hpp"

class AABB
{
public:
	AABB()
	{
		min = Vector3();
		max = Vector3();
	}
	AABB(const Vector3& Min, const Vector3& Max)
	{
		min = Min;
		max = Max;
	}
	AABB operator+(const Vector3& v) const
	{
		return AABB(min + v, max + v);
	}

	bool LineAABBIntersection(const Vector3& start, const Vector3& end, Vector3& intersectionPoint, float &fraction)
	{
		float f_low = 0.0f;
		float f_high = 1.0f;

		if (ClipLine(0, *this, start, end, f_low, f_high) == false)
			return false;
		if (ClipLine(1, *this, start, end, f_low, f_high) == false)
			return false;
		if (ClipLine(2, *this, start, end, f_low, f_high) == false)
			return false;

		Vector3 b = end - start;
		intersectionPoint = start + b * f_low;

		fraction = f_low;
		return true;
	}
	bool ClipLine(const int& d, const AABB& aabb, const Vector3& start, const Vector3& end, float& f_low, float& f_high)
	{
		float f_dim_low = (aabb.min[d] - start[d]) / (end[d] - start[d]);
		float f_dim_high = (aabb.max[d] - start[d]) / (end[d] - start[d]);

		if (f_dim_high < f_dim_low)
		{
			float temp = f_dim_high;
			f_dim_high = f_dim_low;
			f_dim_low = temp;
		}

		if (f_dim_high < f_low || f_dim_low > f_high)
			return false;

		f_low = f_dim_low > f_low ? f_dim_low : f_low;
		f_high = f_dim_high < f_high ? f_dim_high : f_high;

		if (f_low > f_high)
			return false;
		
		return true;
	}
	Vector3 min;
	Vector3 max;
};
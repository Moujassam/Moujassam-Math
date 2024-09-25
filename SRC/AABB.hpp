#pragma once

#include "Vector.hpp"
#include <sycl/sycl.hpp>

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
	const AABB operator+(const Vector3& v) const
	{
		return AABB(min + v, max + v);
	}

	const bool LineAABBIntersection(const Vector3& start, const Vector3& end, Vector3& intersectionPoint, float &fraction) const
	{
		float f_low = 0.0f;
		float f_high = 1.0f;

		if (ClipLine(*this, start, end, f_low, f_high) == false)
			return false;

		Vector3 b = end - start;
		intersectionPoint = start + b * f_low;

		fraction = f_low;
		return true;
	}
	const bool ClipLine(const AABB& aabb, const Vector3& start, const Vector3& end, float& f_low, float& f_high) const
	{
		half3 f_dim_low = (aabb.min.xyz - start.xyz) / (end.xyz - start.xyz);
		half3 f_dim_high = (aabb.max.xyz - start.xyz) / (end.xyz - start.xyz);
		
		short3 comp = f_dim_high < f_dim_low;
		for(int i = 0; i < 3; i++)
			if (comp[i])
			{
				float temp = f_dim_high[i];
				f_dim_high[i] = f_dim_low[i];
				f_dim_low[i] = temp;
			}
		short3 first1 = f_dim_high < f_low;
		short3 second1 = f_dim_low > f_high;
		
		short3 first2 = f_dim_low > f_low;
		short3 second2 = f_dim_high < f_high;
		for(int i = 0; i < 3; i++)
		{
			if (first1[i] || second1[i])
				return false;

			f_low = first2[i] * f_dim_low[i] + !first2[i] * f_low;
			f_high = second2[i] * f_dim_high[i] + !second2[i] * f_high;

			if (f_low > f_high)
				return false;
		}
		
		return true;
	}

	const bool AABBIntersection(const AABB &other) const
	{
		short3 first = min.xyz > other.max.xyz;
		short3 second = max.xyz < other.min.xyz;
		for(char i = 0; i < 3; i++)
		{
			if(first[i])
				return false;
			if(second[i])
				return false;
		}
		return true;
	}

	Vector3 min;
	Vector3 max;
};
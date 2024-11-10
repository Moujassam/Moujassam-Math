#pragma once

#include "Vector.hpp"

class AABB
{
public:
	AABB()
	{
		min = vec3();
		max = vec3();
	}
	AABB(const vec3& Min, const vec3& Max)
	{
		min = Min;
		max = Max;
	}
	const AABB operator+(const vec3& v) const
	{
		return AABB(min + v, max + v);
	}

	const bool LineAABBIntersection(const vec3& start, const vec3& end, vec3& intersectionPoint, float &fraction) const
	{
		float f_low = 0.0f;
		float f_high = 1.0f;

		if (ClipLine(*this, start, end, f_low, f_high) == false)
			return false;

		vec3 b = end - start;
		intersectionPoint = start + b * f_low;

		fraction = f_low;
		return true;
	}
	const bool ClipLine(const AABB& aabb, const vec3& start, const vec3& end, float& f_low, float& f_high) const
	{
		vec3 f_dim_low = (aabb.min - start) / (end - start);
		vec3 f_dim_high = (aabb.max - start) / (end - start);
		
		bvec3 comp = f_dim_high < f_dim_low;
		for(int i = 0; i < 3; i++)
			if (comp[i]) 
			{
				float temp = f_dim_high[i];
				f_dim_high[i] = f_dim_low[i];
				f_dim_low[i] = temp;
			}
		bvec3 first1 = f_dim_high < f_low;
		bvec3 second1 = f_dim_low > f_high;
		
		bvec3 first2 = f_dim_low > f_low;
		bvec3 second2 = f_dim_high < f_high;
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
		bvec3 first = min > other.max;
		bvec3 second = max < other.min;
		for(char i = 0; i < 3; i++)
		{
			if(first[i])
				return false;
			if(second[i])
				return false;
		}
		return true;
	}

	vec3 min;
	vec3 max;
};
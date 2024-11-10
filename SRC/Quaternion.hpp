#pragma once

#include "Vector.hpp"
#include <cassert>

#define toRadians(x) x * 0.01745329251f
#define toDegrees(x) x * 57.2957795131f

class Quaternion
{
public:
    Quaternion()
    {
        w =0 ; v = vec3(0, 0, 0);
    }
    Quaternion(const float &W, const vec3& V)
    {
        w = W;
        v = V;
    }
    Quaternion(const vec3& axis, const float &angle)
    {
        // convert angle to radians
        float a = toRadians(angle);
        float s = std::sin(a / 2);
        w = std::cos(a / 2);
        v = axis * s;
    }

    const Quaternion Inverted() const
    {
        return Quaternion(w, -v);
    }

    const Quaternion operator*(const Quaternion &q) const
    {
        Quaternion r;

	    r.w = w*q.w - v.dot(q.v);
	    r.v = v*q.w + q.v*w + v.cross(q.v);

	    return r;
    }
    const Quaternion operator=(const Quaternion &q)
    {
        w = q.w;
        v = q.v;
        return *this;
    }
    const vec3 operator*(const vec3 &v) const
    {
        const Quaternion p(0, v);
        const Quaternion q = *this;
        return (q * p * q.Inverted()).v;   
    }

    void ToAxisAngle(vec3 &axis, float &angle) const
    {
	    if (v.lengthSqrt() < 0.0001f)
		    axis = vec3(1, 0, 0);
	    else
		    axis = v.normalized();

	    assert(fabs(axis.lengthSqrt() - 1) < 0.000001f);
        angle = acos(w)*2;

	    angle = toDegrees(angle);
    }

    const Quaternion operator^(const float &t) const
    {
        vec3 axis;
        float angle;
        ToAxisAngle(axis, angle);
        return Quaternion(axis, angle * t);
    }

    const Quaternion Slerp(const Quaternion &other, const float &t) const
    {
        const Quaternion &q = *this;
        return ( (other * q.Inverted()) ^ t ) * q;
    }

    float w;
    vec3 v;
};
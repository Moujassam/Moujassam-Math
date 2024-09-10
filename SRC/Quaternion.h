#include "Vector.hpp"
#include <cassert>

#define toRadians(x) x * 0.01745329251f
#define toDegrees(x) x * 57.2957795131f

class Quaternion
{
public:
    Quaternion()
    {
        w =0 ; v = Vector3(0, 0, 0);
    }
    Quaternion(const float &W, const Vector3& V)
    {
        w = W;
        v = V;
    }
    Quaternion(const Vector3& axis, const float &angle)
    {
        // convert angle to radians
        float a = toRadians(angle);
        float s = std::sin(a / 2);
        w = std::cos(a / 2);
        v = axis * s;
    }

    const Quaternion Inverted() const
    {
        return Quaternion(w, Vector3(-v.x, -v.y, -v.z));
    }

    const Quaternion operator*(const Quaternion &q) const
    {
        Quaternion r;

	    r.w = w*q.w - v.DotProduct(q.v);
	    r.v = v*q.w + q.v*w + v.Cross(q.v);

	    return r;
    }
    const Quaternion operator=(const Quaternion &q)
    {
        w = q.w;
        v = q.v;
        return *this;
    }
    const Vector3 operator*(const Vector3 &v) const
    {
        const Quaternion p(0, v);
        const Quaternion q = *this;
        return (q * p * q.Inverted()).v;   
    }

    void ToAxisAngle(Vector3 &axis, float &angle) const
    {
	    if (v.LengthSqrt() < 0.0001f)
		    axis = Vector3(1, 0, 0);
	    else
		    axis = v.Normalize();

	    assert(fabs(axis.LengthSqrt() - 1) < 0.000001f);
        angle = acos(w)*2;

	    angle = toDegrees(angle);
    }

    const Quaternion operator^(const float &t) const
    {
        Vector3 axis;
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
    Vector3 v;
};
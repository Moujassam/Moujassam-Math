#include "AxisAngle.h"

#define toRadians(x) x * 0.01745329251f

//axis need to be a normalized vector
Vector3 RotateVectorAroundAxisAngle(const Vector3& v, const Vector3& axis, const float &angle)
{
    float a = toRadians(angle);
    float sinAngle = sin(a);
    float cosAngle = cos(a);

    return v * cosAngle + axis.Cross(v) * sinAngle + axis * v.DotProduct(axis) * (1 - cosAngle);
}
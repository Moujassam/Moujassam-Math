#pragma once
#include "Vector.hpp"

class Vector3;

const float approach(const float &goal, const float &current, const float &dt);
const float remap(const float& value, const float& low1, const float& high1, const float& low2, const float& high2);
const bool LinePlaneIntersection(const Vector3& plane_point, const Vector3& plane_normal, const Vector3& lineStart, const Vector3& lineEnd, Vector3& intersection, float &fraction);
const Vector3 NearestPointOnSphere(const Vector3 &origin, const float &r, const Vector3 &point);
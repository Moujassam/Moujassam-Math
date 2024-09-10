#pragma once
#include "Vector.hpp"

class Vector3;

float approach(const float &goal, const float &current, const float &dt);
float remap(const float& value, const float& low1, const float& high1, const float& low2, const float& high2);
bool LinePlaneIntersection(const Vector3& plane_point, const Vector3& plane_normal, const Vector3& lineStart, const Vector3& lineEnd, Vector3& intersection, float &fraction);
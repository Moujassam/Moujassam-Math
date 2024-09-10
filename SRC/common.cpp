#include "common.hpp"
float approach(const float &goal, const float &current, const float &dt)
{
    const float diff = goal - current;
    const bool bigger = diff > dt;
    const bool lesser = diff < -dt;
    return (bigger) * (current + dt) + (lesser) * (current - dt) + (!bigger && !lesser) * goal;
}
float remap(const float& value, const float& low1, const float& high1, const float& low2, const float& high2)
{
	float yellow = (value - low1) / (high1 - low1);
	float green = yellow * (high2 - low2) + low2;
    return green;
}
// plane_normal need to be a normilaized vector
bool LinePlaneIntersection(const Vector3& plane_point, const Vector3& plane_normal, const Vector3& lineStart, const Vector3& lineEnd, Vector3& intersection, float &fraction)
{
    Vector3 v = lineEnd - lineStart;
    Vector3 w = plane_point - lineStart;

    float k = w.DotProduct(plane_point)/v.DotProduct(plane_point);

    intersection = lineStart + v * k;

    fraction = k;

    return k >= 0.0f && k <= 1.0f;
}
#pragma once
#include <cmath>
#include <math.h>

class Vector2
{
public:
	Vector2()
	{
		x = 0;
		y = 0;
	}
    Vector2(float X, float Y)
    {
        x = X;
        y = Y;
    }
    float Length() const
    {
        return sqrt(x*x + y*y);
    }
    float LengthSqrt() const
    {
        return x*x + y*y;
    }
    Vector2 operator+(const Vector2 &s) const
    {
        return Vector2(x+s.x, y+s.y);
    }
    Vector2 operator-(const Vector2 &s) const
    {
        return Vector2(x-s.x, y-s.y);
    }
    Vector2 operator*(const float &s) const
    {
        return Vector2(x*s, y*s);
    }
    Vector2 operator/(const float &s) const
    {
        return Vector2(x/s, y/s);
    }
    Vector2 Normalize() const
    {
        return *this / Length();
    }
    float DotProduct(const Vector2& b) const
    {
        return x * b.x + y * b.y;
    }
    float operator[](int i) const
    {
        return (&x)[i];
    }
    float x, y;
};

class Vector3
{
    public:
	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
    Vector3(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    float Length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    float LengthSqrt() const
    {
        return x*x + y*y + z*z;
    }
    Vector3 operator+(const Vector3 &s) const
    {
        return Vector3(x + s.x, y + s.y, z + s.z);
    }
    Vector3 operator-(const Vector3 &s) const
    {
        return Vector3(x - s.x, y - s.y, z - s.z);
    }
    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }
    Vector3 operator*(const float &s) const
    {
        return Vector3(x * s, y * s, z * s);
    }
    Vector3 operator/(const float &s) const
    {
        return Vector3(x/s, y/s, z/s);
    }
    Vector3 Normalize() const
    {
        return *this / Length();
    }
    float DotProduct(const Vector3& b) const
    {
        return x * b.x + y * b.y + z * b.z;
    }
	Vector3 Cross(const Vector3& v) const
	{
		return Vector3(y * v.z - z * v.y, 
                        z * v.x - x * v.z, 
                        x * v.y - y * v.x);
	}
    Vector3 Project(const Vector3& v) const
    {
		return v * (DotProduct(v) / v.LengthSqrt());
    }
    float operator[](int i) const
    {
        return (&x)[i];
    }
    float x, y, z;
};

class Vector4
{
public:
    Vector4()
    {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
    }
    Vector4(float X, float Y, float Z, float W)
    {
        x = X;
        y = Y;
        z = Z;
        w = W;
    }
    float Length() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }
    float LengthSqrt() const
    {
        return x*x + y*y + z*z + w*w;
    }
    Vector4 operator+(const Vector4 &s) const
    {
        return Vector4(x + s.x, y + s.y, z + s.z, w + s.w);
    }
    Vector4 operator-(const Vector4 &s) const
    {
        return Vector4(x - s.x, y - s.y, z - s.z, w - s.w);
    }
    Vector4 operator*(const float &s) const
    {
        return Vector4(x * s, y * s, z * s, w * s);
    }
    Vector4 operator/(const float &s) const
    {
        return Vector4(x/s, y/s, z/s, w/s);
    }
    Vector4 Normalize() const
    {
        return *this / Length();
    }

    float DotProduct(const Vector4& b) const
    {
        return x * b.x + y * b.y + z * b.z + w * b.w;
    }
    float operator[](int i) const
    {
        return (&x)[i];
    }
    float x, y, z, w;
};

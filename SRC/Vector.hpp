#pragma once
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
    const float Length() const
    {
        return sqrt(x*x + y*y);
    }
    const float LengthSqrt() const
    {
        return x*x + y*y;
    }
    const Vector2 operator+(const Vector2 &s) const
    {
        return Vector2(x+s.x, y+s.y);
    }
    const Vector2 operator-(const Vector2 &s) const
    {
        return Vector2(x-s.x, y-s.y);
    }
    const Vector2 operator*(const float &s) const
    {
        return Vector2(x*s, y*s);
    }
    const Vector2 operator/(const float &s) const
    {
        return Vector2(x/s, y/s);
    }
    const Vector2 Normalize() const
    {
        return *this / Length();
    }
    const float DotProduct(const Vector2& b) const
    {
        return x * b.x + y * b.y;
    }
    const float operator[](int i) const
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
    const float Length() const
    {
        return sqrt(x*x + y*y + z*z);
    }
    const float LengthSqrt() const
    {
        return x*x + y*y + z*z;
    }
    const Vector3 operator+(const Vector3 &s) const
    {
        return Vector3(x + s.x, y + s.y, z + s.z);
    }
    const Vector3 operator-(const Vector3 &s) const
    {
        return Vector3(x - s.x, y - s.y, z - s.z);
    }
    const Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }
    const Vector3 operator*(const float &s) const
    {
        return Vector3(x * s, y * s, z * s);
    }
    const Vector3 operator/(const float &s) const
    {
        return Vector3(x/s, y/s, z/s);
    }
    const Vector3 Normalize() const
    {
        return *this / Length();
    }
    const float DotProduct(const Vector3& b) const
    {
        return x * b.x + y * b.y + z * b.z;
    }
	const Vector3 Cross(const Vector3& v) const
	{
		return Vector3(y * v.z - z * v.y,
                        z * v.x - x * v.z,
                        x * v.y - y * v.x);
	}
    const Vector3 Project(const Vector3& v) const
    {
		return v * (DotProduct(v) / v.LengthSqrt());
    }
    const float operator[](int i) const
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
    const float Length() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }
    const float LengthSqrt() const
    {
        return x*x + y*y + z*z + w*w;
    }
    const Vector4 operator+(const Vector4 &s) const
    {
        return Vector4(x + s.x, y + s.y, z + s.z, w + s.w);
    }
    const Vector4 operator-(const Vector4 &s) const
    {
        return Vector4(x - s.x, y - s.y, z - s.z, w - s.w);
    }
    const Vector4 operator*(const float &s) const
    {
        return Vector4(x * s, y * s, z * s, w * s);
    }
    const Vector4 operator/(const float &s) const
    {
        return Vector4(x/s, y/s, z/s, w/s);
    }
    const Vector4 Normalize() const
    {
        return *this / Length();
    }

    const float DotProduct(const Vector4& b) const
    {
        return x * b.x + y * b.y + z * b.z + w * b.w;
    }
    const float operator[](int i) const
    {
        return (&x)[i];
    }
    float x, y, z, w;
};

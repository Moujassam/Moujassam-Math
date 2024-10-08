#pragma once
#include <math.h>
#include <sycl/sycl.hpp>

using namespace sycl;

class Vector2
{
public:
	Vector2()
	{
		xy = float2(0, 0);
	}
	Vector2(float2 xy_init)
	{
		xy = xy_init;
	}
    Vector2(float X, float Y)
    {
        xy[0] = X;
        xy[1] = Y;
    }
    const float Length() const
    {
        return sqrt(dot(xy, xy));//x*x + y*y);
    }
    const float LengthSqrt() const
    {
        return dot(xy, xy);//x*x + y*y;
    }
    const Vector2 operator+(const Vector2 &s) const
    {
        return Vector2(xy + s.xy);//x+s.x, y+s.y);
    }
    const Vector2 operator-(const Vector2 &s) const
    {
        return Vector2(xy - s.xy);//x-s.x, y-s.y);
    }
    const Vector2 operator*(const float &s) const
    {
        return Vector2(xy * s);//x*s, y*s);
    }
    const Vector2 operator/(const float &s) const
    {
        return Vector2(xy / s);//x/s, y/s);
    }
    const Vector2 Normalize() const
    {
        return *this / Length();
    }
    const float DotProduct(const Vector2& b) const
    {
		return dot(xy, b.xy);
        // return x * b.x + y * b.y;
    }
    const float operator[](int i) const
    {
        return (xy)[i];
    }
    
    float2 xy;
};

class Vector3
{
    public:
	Vector3()
	{
		xyz = float3(0, 0, 0);
	}
	Vector3(float3 xyz_init)
	{
		xyz = xyz_init;
	}
	Vector3(float4 xyz_init)
	{ 
		xyz = float3(xyz_init.swizzle<0, 1, 2>());
	}
    Vector3(float X, float Y, float Z)
    {
        xyz[0] = X;
        xyz[1] = Y;
        xyz[2] = Z;
    }
    const float Length() const
    {
        return sqrt(dot(xyz, xyz));//x*x + y*y + z*z);
    }
    const float LengthSqrt() const
    {
        return dot(xyz, xyz);//x*x + y*y + z*z;
    }
    const Vector3 operator+(const Vector3 &s) const
    {
        return Vector3(xyz + s.xyz);//x + s.x, y + s.y, z + s.z);
    }
    const Vector3 operator-(const Vector3 &s) const
    {
        return Vector3(xyz - s.xyz);//x - s.x, y - s.y, z - s.z);
    }
    const Vector3 operator-() const
    {
        return Vector3(-xyz);//-x, -y, -z);
    }
    const Vector3 operator*(const float &s) const
    {
        return Vector3(xyz * s);//x * s, y * s, z * s);
    }
    const Vector3 operator/(const float &s) const
    {
        return Vector3(xyz / s);//x/s, y/s, z/s);
    }
    const Vector3 Normalize() const
    {
        return *this / Length();
    }
    const float DotProduct(const Vector3& b) const
    {
        return dot(xyz, b.xyz);//x * b.x + y * b.y + z * b.z;
    }
	const Vector3 Cross(const Vector3& v) const
	{
		return cross(xyz, v.xyz);
		// return Vector3(y * v.z - z * v.y,
        //                 z * v.x - x * v.z,
        //                 x * v.y - y * v.x);
	}
    const Vector3 Project(const Vector3& v) const
    {
		return v * (DotProduct(v) / v.LengthSqrt());
    }
    const float &operator[](const int i) const
    {
        return (xyz)[i];
    }
	const float &x() const {return xyz.x();}
	const float &y() const {return xyz.y();}
	const float &z() const {return xyz.z();}

    float3 xyz;
};

template<>
struct sycl::is_device_copyable<Vector3> : std::true_type {};

class Vector4
{
public:
    Vector4()
    {
		xyzw = float4(0, 0, 0, 0);
    }
	Vector4(float4 xyzw_init)
	{
		xyzw = xyzw_init;
	}
    Vector4(float X, float Y, float Z, float W)
    {
        xyzw[0] = X;
        xyzw[1] = Y;
        xyzw[2] = Z;
        xyzw[3] = W;
    }
    const float Length() const
    {
        return sqrt(dot(xyzw, xyzw));//x*x + y*y + z*z + w*w);
    }
    const float LengthSqrt() const
    {
        return dot(xyzw, xyzw);//x*x + y*y + z*z + w*w;
    }
    const Vector4 operator+(const Vector4 &s) const
    {
        return Vector4(xyzw + s.xyzw);//x + s.x, y + s.y, z + s.z, w + s.w);
    }
    const Vector4 operator-(const Vector4 &s) const
    {
        return Vector4(xyzw - s.xyzw);//x - s.x, y - s.y, z - s.z, w - s.w);
    }
    const Vector4 operator*(const float &s) const
    {
        return Vector4(xyzw * s);//x * s, y * s, z * s, w * s);
    }
    const Vector4 operator/(const float &s) const
    {
        return Vector4(xyzw / s);//x/s, y/s, z/s, w/s);
    }
    const Vector4 Normalize() const
    {
        return *this / Length();
    }

    const float DotProduct(const Vector4& b) const
    {
        return dot(xyzw, b.xyzw);
		// return x * b.x + y * b.y + z * b.z + w * b.w;
    }
    const float operator[](int i) const
    {
        return (xyzw)[i];
    }
    float4 xyzw;
};

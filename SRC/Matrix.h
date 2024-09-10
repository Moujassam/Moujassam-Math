#pragma once

#include <cstring>
#include "Vector.hpp"

#define toRadians(x) x * 0.01745329251f
						 
class Matrix4x4
{
public:
	Matrix4x4()
	{
		for (int i = 0; i < 4 * 4; i++)
			m[i] = 0.0f;
	}

	Matrix4x4(const Vector3 &forward, const Vector3 &up, const Vector3 &right, const Vector3 &translate)
	{
		m[0 + 0 * 4] = forward.x;
		m[0 + 1 * 4] = forward.y;
		m[0 + 2 * 4] = forward.z;
		m[0 + 3 * 4] = 0.0f;

		m[1 + 0 * 4] = up.x;
		m[1 + 1 * 4] = up.y;
		m[1 + 2 * 4] = up.z;
		m[1 + 3 * 4] = 0.0f;

		m[2 + 0 * 4] = right.x;
		m[2 + 1 * 4] = right.y;
		m[2 + 2 * 4] = right.z;
		m[2 + 3 * 4] = 0.0f;

		m[0 + 3 * 4] = translate.x;
		m[1 + 3 * 4] = translate.y;
		m[2 + 3 * 4] = translate.z;
		m[3 + 3 * 4] = 1.0f;
	}
	Matrix4x4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			m[i] = 0.0f;

		m[0 + 0 * 4] = diagonal;
		m[1 + 1 * 4] = diagonal;
		m[2 + 2 * 4] = diagonal;
		m[3 + 3 * 4] = diagonal;
	}

	Matrix4x4(float* elements)
	{
		for (int i = 0; i < 4 * 4; i++)
			m[i] = elements[i];
	}

	static Matrix4x4 LookAt(const Vector3& camera, const Vector3& object, const Vector3& up)
	{
		Vector3 forward = (object - camera).Normalize();
		Vector3 right = up.Cross(forward).Normalize();
		Vector3 newUp = forward.Cross(right);

		return Matrix4x4(forward, newUp, right, camera);
	}

	static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 0 * 4] = 2.0f / (right - left);
		result.m[1 + 1 * 4] = 2.0f / (top - bottom);
		result.m[2 + 2 * 4] = 2.0f / (near - far);

		result.m[0 + 3 * 4] = (left + right) / (left - right);
		result.m[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.m[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	static Matrix4x4 Perspective(float fov, float aspectRatio, float near, float far)
	{
		Matrix4x4 result(1.0f);

		float q = 1.0f / tan(0.5f * fov);
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.m[0 + 0 * 4] = a;
		result.m[1 + 1 * 4] = q;
		result.m[2 + 2 * 4] = b;
		result.m[3 + 2 * 4] = -1.0f;
		result.m[2 + 3 * 4] = c;

		return result;
	}

	static Matrix4x4 Translation(const Vector3& translation)
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 3 * 4] = translation.x;
		result.m[1 + 3 * 4] = translation.y;
		result.m[2 + 3 * 4] = translation.z;

		return result;
	}

	static Matrix4x4 Rotation(float angle, const Vector3& axis)
	{
		Matrix4x4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.m[0 + 0 * 4] = x * omc + c;
		result.m[1 + 0 * 4] = y * x * omc + z * s;
		result.m[2 + 0 * 4] = x * z * omc - y * s;

		result.m[0 + 1 * 4] = x * y * omc - z * s;
		result.m[1 + 1 * 4] = y * omc + c;
		result.m[2 + 1 * 4] = y * z * omc + x * s;

		result.m[0 + 2 * 4] = x * z * omc + y * s;
		result.m[1 + 2 * 4] = y * z * omc - x * s;
		result.m[2 + 2 * 4] = z * omc + c;

		return result;
	}

	static Matrix4x4 Scale(const Vector3& scale)
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 0 * 4] = scale.x;
		result.m[1 + 1 * 4] = scale.y;
		result.m[2 + 2 * 4] = scale.z;

		return result;
	}

	

	static Matrix4x4 Identity()
	{
		return Matrix4x4(1.0f);
	}

	Matrix4x4& Multiply(const Matrix4x4& other)
	{
		float data[16] = { 0 };
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += m[x + e * 4] * other.m[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(m, data, 4 * 4 * sizeof(float));
		return *this;
	}

	friend Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right)
	{
		return left.Multiply(right);
	}

	Matrix4x4& operator*=(const Matrix4x4& other)
	{
		return Multiply(other);
	}
	Matrix4x4& operator=(const Matrix4x4& other)
	{
		memcpy(m, other.m, 4 * 4 * sizeof(float));
		return *this;
	}

	Vector3 Multiply(const Vector3& other) const
	{
		return Vector3(
			m[0 + 0 * 4] * other.x + m[0 + 1 * 4] * other.y + m[0 + 2 * 4] * other.z + m[0 + 3 * 4],
			m[1 + 0 * 4] * other.x + m[1 + 1 * 4] * other.y + m[1 + 2 * 4] * other.z + m[1 + 3 * 4],
			m[2 + 0 * 4] * other.x + m[2 + 1 * 4] * other.y + m[2 + 2 * 4] * other.z + m[2 + 3 * 4]
		);
	}

	friend Vector3 operator*(const Matrix4x4& left, const Vector3& right)
	{
		return left.Multiply(right);
	}

	Matrix4x4 ScaleInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 0 * 4] = 1.0f / m[0 + 0 * 4];
		result.m[1 + 1 * 4] = 1.0f / m[1 + 1 * 4];
		result.m[2 + 2 * 4] = 1.0f / m[2 + 2 * 4];

		return result;
	}

	Matrix4x4 Transpose() const
	{
		Matrix4x4 result(1.0f);

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				result.m[x + y * 4] = m[y + x * 4];
			}
		}
		return result;
	}

	Matrix4x4 RotationInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 0 * 4] = m[0 + 0 * 4];
		result.m[1 + 0 * 4] = m[0 + 1 * 4];
		result.m[2 + 0 * 4] = m[0 + 2 * 4];

		result.m[0 + 1 * 4] = m[1 + 0 * 4];
		result.m[1 + 1 * 4] = m[1 + 1 * 4];
		result.m[2 + 1 * 4] = m[1 + 2 * 4];

		result.m[0 + 2 * 4] = m[2 + 0 * 4];
		result.m[1 + 2 * 4] = m[2 + 1 * 4];
		result.m[2 + 2 * 4] = m[2 + 2 * 4];

		return result;
	}

	Matrix4x4 TranslateInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0 + 3 * 4] = -m[0 + 3 * 4];
		result.m[1 + 3 * 4] = -m[1 + 3 * 4];
		result.m[2 + 3 * 4] = -m[2 + 3 * 4];

		return result;
	}

	Matrix4x4 TRInverse() const
	{
		return TranslateInverse() * RotationInverse();
	}
	
	float m[4 * 4];
};
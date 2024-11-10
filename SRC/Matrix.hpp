#pragma once

#include "Vector.hpp"

#define toRadians(x) x * 0.01745329251f


class Matrix4x4
{
public:
	Matrix4x4()
	{
		*this = Matrix4x4::Identity();
	}
	
	~Matrix4x4(){}

	Matrix4x4(const Matrix4x4 &other)
	{
		for(int i = 0; i < 4; i++)
			m[i] = other.m[i];
	}

	const Matrix4x4 &operator=(const Matrix4x4 &other)
	{
		for(int i = 0; i < 4; i++)
			m[i] = other.m[i];
		return *this;
	}
	
	Matrix4x4(const vec3 &forward, const vec3 &up, const vec3 &right, const vec3 &translate)
	{
		m[0] = vec4(forward, 0.0f);
		// m[0][0] = forward.x();
		// m[0][1] = forward.y();
		// m[0][2] = forward.z();
		// m[0][3] = 0.0f;

		m[1] = vec4(up, 0.0f);
		// m[1][0] = up.x();
		// m[1][1] = up.y();
		// m[1][2] = up.z();
		// m[1][3] = 0.0f;

		m[2] = vec4(right, 0.0f);
		// m[2][0] = right.x();
		// m[2][1] = right.y();
		// m[2][2] = right.z();
		// m[2][3] = 0.0f;

		m[0][3] = translate[0];
		m[1][3] = translate[1];
		m[2][3] = translate[2];
		m[3][3] = 1.0f;
	}
	Matrix4x4(float diagonal)
	{
		for (int i = 0; i < 4; i++)
			m[i] = vec4(0.0f);

		m[0][0] = diagonal;
		m[1][1] = diagonal;
		m[2][2] = diagonal;
		m[3][3] = diagonal;
	}

	Matrix4x4(float* elements)
	{
		for (int i = 0; i < 4; i++)
			m[i] = vec4(elements[0 + i * 4], elements[1 + i * 4], elements[2 + i * 4], elements[3 + i * 4]);
	}
	
	Matrix4x4(vec4* elements)
	{
		for (int i = 0; i < 4; i++)
			m[i] = elements[i];
	}

	static const Matrix4x4 LookAt(const vec3& camera, const vec3& object, const vec3& up)
	{
		vec3 forward = (object - camera).normalized();
		vec3 right = up.cross(forward).normalized();
		vec3 newUp = forward.cross(right);

		return Matrix4x4(forward, newUp, right, camera);
	}

	static const Matrix4x4 Orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
	{
		Matrix4x4 result(1.0f);

		result.m[0][0] = 2.0f / (right - left);
		result.m[1][1] = 2.0f / (top - bottom);
		result.m[2][2] = 2.0f / (near - far);

		result.m[0][3] = (left + right) / (left - right);
		result.m[1][3] = (bottom + top) / (bottom - top);
		result.m[2][3] = (far + near) / (far - near);

		return result;
	}

	static const Matrix4x4 Perspective(const float fov, const float aspectRatio, const float near, const float far)
	{
		Matrix4x4 result(1.0f);

		float q = 1.0f / tan(0.5f * fov);
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.m[0][0] = a;
		result.m[1][1] = q;
		result.m[2][2] = b;
		result.m[3][2] = -1.0f;
		result.m[2][3] = c;

		return result;
	}

	static const Matrix4x4 Translation(const vec3& translation)
	{
		Matrix4x4 result(1.0f);

		result.m[0][3] = translation.x();
		result.m[1][3] = translation.y();
		result.m[2][3] = translation.z();

		return result;
	}

	static const Matrix4x4 Rotation(const float angle, const vec3& axis)
	{
		Matrix4x4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x();
		float y = axis.y();
		float z = axis.z();

		result.m[0][0] = x * omc + c;
		result.m[1][0] = y * x * omc + z * s;
		result.m[2][0] = x * z * omc - y * s;

		result.m[0][1] = x * y * omc - z * s;
		result.m[1][1] = y * omc + c;
		result.m[2][1] = y * z * omc + x * s;

		result.m[0][2] = x * z * omc + y * s;
		result.m[1][2] = y * z * omc - x * s;
		result.m[2][2] = z * omc + c;

		return result;
	}

	static const Matrix4x4 Scale(const vec3& scale)
	{
		Matrix4x4 result(1.0f);

		result.m[0][0] = scale.x();
		result.m[1][1] = scale.y();
		result.m[2][2] = scale.z();

		return result;
	}

	

	static const Matrix4x4 Identity()
	{
		return Matrix4x4(1.0f);
	}

	friend const Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& other)
	{
		Matrix4x4 data;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				vec4 oth2 = vec4(other.m[0][y], other.m[1][y], other.m[2][y], other.m[3][y]);
				float sum = (left.m[x].dot(oth2));
				data.m[x][y] = sum;
				
				// float sum = 0.0f;

				// for (int e = 0; e < 4; e++)
				// {
				// 	sum += left.m[x][e] * other.m[e][y];
				// }
				// data.m[x][y] = sum;

			}
		}
		return data;
	}

	const vec3 TransformDirection(const vec3 &v) const
	{
		vec4 vec(v, 0);
		return vec3(m[0].dot( vec), m[1].dot(vec), m[2].dot(vec));
		// return vec3(
		// 	m[0 + 0 * 4] * v.x() + m[0 + 1 * 4] * v.y() + m[0 + 2 * 4] * v.z(),
		// 	m[1 + 0 * 4] * v.x() + m[1 + 1 * 4] * v.y() + m[1 + 2 * 4] * v.z(),
		// 	m[2 + 0 * 4] * v.x() + m[2 + 1 * 4] * v.y() + m[2 + 2 * 4] * v.z()
		// );
	}

	const Matrix4x4 operator*=(const Matrix4x4& other) const
	{
		return (*this)*(other);
	}

	const vec3 Multiply(const vec3& other) const
	{
		vec4 vec(other, 1);
		return vec3(m[0].dot( vec), m[1].dot(vec), m[2].dot(vec));
		// return vec3(
		// 	m[0 + 0 * 4] * other.x() + m[0 + 1 * 4] * other.y() + m[0 + 2 * 4] * other.z() + m[0 + 3 * 4],
		// 	m[1 + 0 * 4] * other.x() + m[1 + 1 * 4] * other.y() + m[1 + 2 * 4] * other.z() + m[1 + 3 * 4],
		// 	m[2 + 0 * 4] * other.x() + m[2 + 1 * 4] * other.y() + m[2 + 2 * 4] * other.z() + m[2 + 3 * 4]
		// );
	}

	friend const vec3 operator*(const Matrix4x4& left, const vec3& right)
	{
		return left.Multiply(right);
	}

	const Matrix4x4 ScaleInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0][0] = 1.0f / m[0][0];
		result.m[1][1] = 1.0f / m[1][1];
		result.m[2][2] = 1.0f / m[2][2];

		return result;
	}

	const Matrix4x4 Transpose() const
	{
		Matrix4x4 result(1.0f);

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				result.m[x][y] = m[y][x];
			}
		}
		return result;
	}

	const Matrix4x4 RotationInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0][0] = m[0][0];
		result.m[1][0] = m[0][1];
		result.m[2][0] = m[0][2];

		result.m[0][1] = m[1][0];
		result.m[1][1] = m[1][1];
		result.m[2][1] = m[1][2];

		result.m[0][2] = m[2][0];
		result.m[1][2] = m[2][1];
		result.m[2][2] = m[2][2];

		return result;
	}

	const Matrix4x4 TranslateInverse() const
	{
		Matrix4x4 result(1.0f);

		result.m[0][3] = -m[0][3];
		result.m[1][3] = -m[1][3];
		result.m[2][3] = -m[2][3];

		return result;
	}

	const Matrix4x4 TRInverse() const
	{
		return TranslateInverse() * RotationInverse();
	}
	
	vec4 m[4];
};

#pragma once
#include <array>
#include <cmath> 

template <typename T, std::size_t N>
class Vector {
private:
    std::array<T, N> data;
public:
    Vector() = default;
    Vector(const std::array<T, N>& data) : data(data) {}
    Vector(std::array<T, N>&& data) : data(std::move(data)) {}
    Vector(const Vector<T, N>& other) : data(other.data) {}
    Vector(Vector<T, N>&& other) : data(std::move(other.data)) {}
    Vector(std::initializer_list<T> list) {
        std::size_t i = 0;
        for (const T& value : list) {
            data[i++] = value;
        }
    }
    Vector(Vector<T, N - 1> other, T value) {
        for (std::size_t i = 0; i < N - 1; ++i) {
            data[i] = other[i];
        }
        data[N - 1] = value;
    }
    Vector(T value, Vector<T, N - 1> other) {
        data[0] = value;
        for (std::size_t i = 0; i < N - 1; ++i) {
            data[i + 1] = other[i];
        }
    }

    Vector(Vector<T, N-1> other)
    {
        for (int i = 0; i < N - 1; i++)
            data[i] = other[i];
        data[N - 1] = 0;
    }
    Vector(T value) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = value;
        }
    }
    Vector(T x, T y) {
        static_assert(N == 2, "Vector must have 2 components");
        data[0] = x;
        data[1] = y;
    }   
    Vector(T x, T y, T z) {
        static_assert(N == 3, "Vector must have 3 components");
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    Vector(T x, T y, T z, T w) {
        static_assert(N == 4, "Vector must have 4 components");
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }
    Vector<T, N>& operator=(const Vector<T, N>& other) {
        data = other.data;
        return *this;
    }
    Vector<T, N>& operator=(Vector<T, N>&& other) {
        data = std::move(other.data);
        return *this;
    }
    T& operator[](std::size_t i) {
        return data[i];
    }
    const T& operator[](std::size_t i) const {
        return data[i];
    }
    Vector<T, N> operator+(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }
    Vector<T, N> operator-(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }
    Vector<T, N> operator*(T scalar) const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] * scalar;
        }
        return result;
    }
    Vector<T, N> operator/(T scalar) const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] / scalar;
        }
        return result;
    }
    Vector operator/(const Vector& other) const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] / other[i];
        }
        return result;
    }
    Vector<T, N>& operator+=(const Vector<T, N>& other) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] += other[i];
        }
        return *this;
    }
    Vector<T, N>& operator-=(const Vector<T, N>& other) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] -= other[i];
        }
        return *this;
    }
    Vector<T, N>& operator*=(T scalar) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }
    Vector<T, N>& operator/=(T scalar) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }
    Vector<T, N> operator-() const {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = -data[i];
        }
        return result;
    }
    T dot(const Vector<T, N>& other) const {
        T result = 0;
        for (std::size_t i = 0; i < N; ++i) {
            result += data[i] * other[i];
        }
        return result;
    }
    T lengthSqrt() const {
        return dot(*this);
    }
    T length() const {
        return std::sqrt(lengthSqrt());
    }
    Vector<T, N> normalized() const {
        return *this / length();
    }

    Vector<T, N> cross(const Vector<T, N>& other) const {
        static_assert(N == 3, "cross product is only defined for 3D vectors");
        return {
            data[1] * other[2] - data[2] * other[1],
            data[2] * other[0] - data[0] * other[2],
            data[0] * other[1] - data[1] * other[0]
        };
    }
    Vector<T, N> reflect(const Vector<T, N>& normal) const {
        return *this - 2 * dot(normal) * normal;
    }
    Vector<T, N> refract(const Vector<T, N>& normal, T eta) const {
        T k = 1 - eta * eta * (1 - dot(normal) * dot(normal));
        if (k < 0) {
            return {};
        }
        return eta * *this - (eta * dot(normal) + std::sqrt(k)) * normal;
    }
    T x() const {
        static_assert(N >= 1, "Vector must have at least 1 component");
        return data[0];
    }
    T y() const {
        static_assert(N >= 2, "Vector must have at least 2 components");
        return data[1];
    }
    T z() const {
        static_assert(N >= 3, "Vector must have at least 3 components");
        return data[2];
    }
    T w() const {
        static_assert(N >= 4, "Vector must have at least 4 components");
        return data[3];
    }
    std::size_t size() const {
        return N;
    }
    const T* ptr() const {
        return data.data();
    }
    T* ptr() {
        return data.data();
    }
    T &operator[](int i)
    {
        return data[i];
    }
    const T &operator[](int i) const
    {
        return data[i];
    }
    Vector<bool, N> operator<(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] < other[i];
        }
        return result;
    }
    Vector<bool, N> operator>(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] > other[i];
        }
        return result;
    }

    Vector<bool, N> operator<=(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] <= other[i];
        }
        return result;
    }

    Vector<bool, N> operator>=(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] >= other[i];
        }
        return result;
    }

    Vector<bool, N> operator==(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] == other[i];
        }
        return result;
    }

    Vector<bool, N> operator!=(const Vector<T, N>& other) const {
        Vector<bool, N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result[i] = data[i] != other[i];
        }
        return result;
    }
};

using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;
using dvec2 = Vector<double, 2>;
using dvec3 = Vector<double, 3>;
using dvec4 = Vector<double, 4>;
using ivec2 = Vector<int, 2>;
using ivec3 = Vector<int, 3>;
using ivec4 = Vector<int, 4>;
using uvec2 = Vector<unsigned int, 2>;
using uvec3 = Vector<unsigned int, 3>;
using uvec4 = Vector<unsigned int, 4>;
using bvec2 = Vector<bool, 2>;
using bvec3 = Vector<bool, 3>;
using bvec4 = Vector<bool, 4>;


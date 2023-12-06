#pragma once
#include "Utils.h"

template <typename T>
struct Vec2 {
    T x, y;

    // Constructors
    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

template <typename T>
struct Vec3 {
    T x, y, z;

    // Constructors
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    void set(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

template <typename T>
Vec3<T> operator*(const Vec3<T>& left, const Vec3<T>& right)
{
    Vec3<T> result;
    result.x = left.x * right.x;
    result.y = left.y * right.y;
    result.z = left.z * right.z;

    return result;
}

template <typename T>
bool operator==(const Vec3<T>& left, const Vec3<T>& right)
{
    if (left.x == right.x) {
        if (left.y == right.y) {
            if (left.z == right.z) {
                return true;
            }
        }
    }

    return false;
}



template <typename T>
struct Vec4 {
    T x, y, z, c;

    // Constructors
    Vec4() : x(0), y(0), z(0), c(0) {}
    Vec4(T x, T y, T z, T c) : x(x), y(y), z(z), c(c) {}

    void set(T x, T y, T z, T c) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->c = c;
    }
};

template <typename T>
Vec4<T> operator*(const Vec4<T>& left, const Vec4<T>& right)
{
    Vec4<T> result;
    result.x = left.x * right.x;
    result.y = left.y * right.y;
    result.z = left.z * right.z;
    result.c = left.c * right.c;

    return result;
}


struct mat4 {

    float elements[16];

    mat4();
    mat4(float diagonal) {

        for (int i = 0; i < 4 * 4; i++)
            elements[i] = 0.0f;

        elements[0 + 0 * 4] = diagonal;
        elements[1 + 1 * 4] = diagonal;
        elements[2 + 2 * 4] = diagonal;
        elements[3 + 3 * 4] = diagonal;
    }

    static mat4 identity() {
        return mat4(1.0f);
    }

    Vec4<float> getColumn(int index)
    {
        index *= 4;
        return Vec4<float>(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
    }

    mat4& multiply(const mat4& other) {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                float sum = 0.0f;
                for (int e = 0; e < 4; e++)
                {
                    sum += elements[x + e * 4] * other.elements[e + y * 4];
                }
                elements[x + y * 4] = sum;
            }
        }

        return *this;
    }

    friend mat4 operator*(mat4 left, const mat4& right) {
        return left.multiply(right);
    }

    mat4& operator*=(const mat4& other) {
        return multiply(other);
    }

    static mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
        mat4 result(1.0f);

        result.elements[0 + 0 * 4] = 2.0f / (right - left);

        result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

        result.elements[2 + 2 * 4] = 2.0f / (near - far);

        result.elements[0 + 3 * 4] = (left + right) / (left - right);
        result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
        result.elements[2 + 3 * 4] = (far + near) / (far - near);

        return result;
    }

    static mat4 perspective(float fov, float aspectRatio, float near, float far) {
        mat4 result(1.0f);

        float q = 1.0f / tan(toRadians(0.5f * fov));
        float a = q / aspectRatio;

        float b = (near + far) / (near - far);
        float c = (2.0f * near * far) / (near - far);

        result.elements[0 + 0 * 4] = a;
        result.elements[1 + 1 * 4] = q;
        result.elements[2 + 2 * 4] = b;
        result.elements[3 + 2 * 4] = -1.0f;
        result.elements[2 + 3 * 4] = c;

        return result;
    }

    static mat4 translation(const Vec3<float>& translation) {
        mat4 result(1.0f);

        result.elements[0 + 3 * 4] = translation.x;
        result.elements[1 + 3 * 4] = translation.y;
        result.elements[2 + 3 * 4] = translation.z;

        return result;
    }

    static mat4 rotation(float angle, const Vec3<float>& axis) {
        mat4 result(1.0f);

        float r = toRadians(angle);
        float c = cos(r);
        float s = sin(r);
        float omc = 1.0f - c;

        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        result.elements[0 + 0 * 4] = x * omc + c;
        result.elements[1 + 0 * 4] = y * x * omc + z * s;
        result.elements[2 + 0 * 4] = x * z * omc - y * s;

        result.elements[0 + 1 * 4] = x * y * omc - z * s;
        result.elements[1 + 1 * 4] = y * omc + c;
        result.elements[2 + 1 * 4] = y * z * omc + x * s;

        result.elements[0 + 2 * 4] = x * z * omc + y * s;
        result.elements[1 + 2 * 4] = y * z * omc - x * s;
        result.elements[2 + 2 * 4] = z * omc + c;

        return result;
    }

    static mat4 scale(const Vec3<float>& scale) {
        mat4 result(1.0f);

        result.elements[0 + 0 * 4] = scale.x;
        result.elements[1 + 1 * 4] = scale.y;
        result.elements[2 + 2 * 4] = scale.z;

        return result;
    }

};
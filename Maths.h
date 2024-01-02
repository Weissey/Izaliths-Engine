#pragma once
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
inline float toRadians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}

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

    Vec3<T>& operator+=(const Vec3<T>& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3<T>& operator-=(const Vec3<T>& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3<T>& operator*(const Vec3<T>& right)
    {
        this->x = this->x * right.x;
        this->y = this->y * right.y;
        this->z = this->z * right.z;

        return *this;
    }

    Vec3<T>& operator*(const float& right)
    {
        this->x = right * this->x;
        this->y = right * this->y;
        this->z = right * this->z;

        return *this;
    }

};


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

        for (int i = 0; i < 4 * 4; i++) {
            elements[i] = 0.0f;
        }

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

    mat4 operator*(const mat4& other) const {
        mat4 result(0.0f);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    result.elements[i * 4 + j] += elements[i * 4 + k] * other.elements[k * 4 + j];
                }
            }
        }
        return result;
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
        mat4 result(1.0f); // Initialize to identity matrix

        float q = 1.0f / tan(toRadians(0.5f * fov));
        float a = q / aspectRatio;
        float b = (near + far) / (near - far);
        float c = (2.0f * near * far) / (near - far);

        // Set elements of the perspective matrix
        result.elements[0 + 0 * 4] = a;
        result.elements[1 + 1 * 4] = q;
        result.elements[2 + 2 * 4] = b;
        result.elements[3 + 2 * 4] = -1.0f;
        result.elements[2 + 3 * 4] = c;

        // Print the resulting matrix for debugging
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << "M[" << i << "][" << j << "] = " << result.elements[i + j * 4] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        return result;
    }


    static mat4 translation(const Vec3<float>& translation) {
        mat4 result(1.0f);

        result.elements[0 + 3 * 4] = translation.x;
        result.elements[1 + 3 * 4] = translation.y;
        result.elements[2 + 3 * 4] = translation.z;

        return result;
    }

    static mat4 rotation(const Vec3<float>& angles) {
        mat4 result(1.0f);

        float radX = toRadians(angles.x);
        float radY = toRadians(angles.y);
        float radZ = toRadians(angles.z);

        float cx = cos(radX);
        float sx = sin(radX);
        float cy = cos(radY);
        float sy = sin(radY);
        float cz = cos(radZ);
        float sz = sin(radZ);

        result.elements[0] = cy * cz + sx * sy * sz;
        result.elements[1] = cz * sx * sy - cy * sz;
        result.elements[2] = cx * sy;
        result.elements[4] = cx * sz;
        result.elements[5] = cx * cz;
        result.elements[6] = -sx;
        result.elements[8] = cy * sx * sz - cz * sy;
        result.elements[9] = cy * cz * sx + sy * sz;
        result.elements[10] = cx * cy;

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

namespace maths {
    inline const float clamp(float value, float min, float max) {
        return (value < min) ? min : ((value > max) ? max : value);
    }
}

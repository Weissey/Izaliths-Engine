#pragma once

template <typename T>
class Vec2 {
public:
    T x, y;

    // Constructors
    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

};

template <typename T>
class Vec3 {
public:
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
class Vec4 {
public:
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
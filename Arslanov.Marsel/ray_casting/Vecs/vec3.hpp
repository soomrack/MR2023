#pragma once
#include "vec2.hpp"

class vec3
{
protected:
    using data_type = double;

    data_type x{0};
    data_type y{0};
    data_type z{0};

public:
    vec3() = default;
    vec3(data_type value) : x(value), y(value), z(value){};
    vec3(data_type x, data_type y, data_type z) : x(x), y(y), z(z){};
    vec3(data_type x, vec2 v2) : x(x), y(v2.get_x()), z(v2.get_y()){};
    vec3(const vec3& other) : x(other.x), y(other.y), z(other.z) {}
    ~vec3() = default;

    data_type get_x() { return x; }
    data_type get_y() { return y; }
    data_type get_z() { return z; }
    void set_x(data_type x) { this->x = x; }
    void set_y(data_type y) { this->y = y; }
    void set_z(data_type z) { this->z = z; }

    double length() { return sqrt(x * x + y * y + z * z); }
    vec3& norm() {
        *this /= vec3(length());
        return *this;
    }
    double dot_product(const vec3& other) {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3& operator=(const vec3& rhs) {
        if (this == &rhs) {
            return *this;
        }
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;

        return *this;
    }

    vec3 operator+(const vec3& rhs) {
        return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    vec3 operator-(const vec3& rhs) {
        return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    vec3 operator*(const vec3& rhs) {
        return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
    }
    vec3 operator/(const vec3& rhs) {
        return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
    }
    vec3& operator+=(const vec3& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }
    vec3& operator-=(const vec3& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }
    vec3& operator*=(const vec3& rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }
    vec3& operator/=(const vec3& rhs) {
        this->x /= rhs.x;
        this->y /= rhs.y;
        this->z /= rhs.z;
        return *this;
    }
};
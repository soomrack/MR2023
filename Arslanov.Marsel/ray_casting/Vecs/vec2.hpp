#pragma once
#include "math.h"

class vec2
{
protected:
    using data_type = double;

    data_type x{0};
    data_type y{0};

public:
    vec2() = default;
    vec2(data_type value) : x(value), y(value){};
    vec2(data_type x, data_type y) : x(x), y(y){};
    vec2(const vec2& other) : x(other.x), y(other.y) {}
    ~vec2() = default;

    data_type get_x() { return x; }
    data_type get_y() { return y; }
    void set_x(data_type x) { this->x = x; }
    void set_y(data_type y) { this->y = y; }

    double length() { return sqrt(x * x + y * y); }
    vec2& norm() {
        *this /= vec2(length());
        return *this;
    }
    double dot_product(const vec2& vec2) { return x * vec2.x + y * vec2.y; }

    vec2& operator=(const vec2& rhs) {
        if (this == &rhs) {
            return *this;
        }
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    vec2 operator+(const vec2& rhs) { return vec2(x + rhs.x, y + rhs.y); }
    vec2 operator-(const vec2& rhs) { return vec2(x - rhs.x, y - rhs.y); }
    vec2 operator*(const vec2& rhs) { return vec2(x * rhs.x, y * rhs.y); }
    vec2 operator/(const vec2& rhs) { return vec2(x / rhs.x, y / rhs.y); }
    vec2& operator+=(const vec2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    vec2& operator-=(const vec2& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    vec2& operator*=(const vec2& rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        return *this;
    }
    vec2& operator/=(const vec2& rhs) {
        this->x /= rhs.x;
        this->y /= rhs.y;
        return *this;
    }
};
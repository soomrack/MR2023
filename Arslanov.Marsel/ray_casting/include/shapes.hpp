#pragma once
#include <math.h>

#include "vec2.hpp"
#include "vec3.hpp"

enum class Shape_type { SPHERE, PLANE, CUBE };

class Abstract_shape
{
protected:
    vec3 coordinates;

public:
    Abstract_shape(const vec3& coordinates) : coordinates(coordinates){};
    virtual vec2 ray_interspect(vec3 ro, vec3 rd) = 0;
};

class Sphere : public Abstract_shape
{
public:
    static const Shape_type shape_type = Shape_type::SPHERE;

private:
    double radius{0};

public:
    Sphere() = delete;
    Sphere(const vec3& coordinates, double radius)
            : Abstract_shape(coordinates), radius(radius) {}
    ~Sphere() = default;

    vec2 ray_interspect(vec3 ro, vec3 rd) {
        vec3 dist = ro - coordinates;  // vector form ro to center of sphere
        double b = rd.dot_product(dist);
        double c = dist.dot_product(dist) - radius * radius;
        double d = b * b - c;
        if (d < 0.0) return vec2(-1.0);
        d = sqrt(d);
        return vec2(-b - d, -b + d);
    }
};

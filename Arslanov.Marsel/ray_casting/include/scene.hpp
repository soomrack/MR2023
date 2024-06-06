#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "shapes.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

class Scene
{
private:
    static constexpr char gradient[] = {" .:!/r(l1Z4H9W8$@"};

private:
    vec3 dimension{0};
    vec3 camera{0};
    char* projection;
    vec3 light_dir{0};

    std::vector<Abstract_shape*> shapes;

public:
    Scene() = delete;
    Scene(const vec3& dimension, const vec3& camera);
    ~Scene();

    double window_aspect() {
        return static_cast<double>(dimension.get_y()) /
               static_cast<double>(dimension.get_z());
    }
    double pixel_aspect() { return 11.0 / 24.0; }  // pixels are not square
    double aspect() { return window_aspect() * pixel_aspect(); }

    size_t gradient_size() { return sizeof(gradient) - 1; }
    size_t size2d() { return dimension.get_y() * dimension.get_z(); }

    void set_light_dir(const vec3& light_dir);

    void add_shape(Abstract_shape* shape);

    void update();

    friend std::ostream& operator<<(std::ostream& os, Scene& scene) {
        if (!scene.size2d()) {
            os << "Scene is empty";
            return os;
        }
        os << scene.projection;
        return os;
    };
};
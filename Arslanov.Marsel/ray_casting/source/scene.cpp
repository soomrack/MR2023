#include "scene.hpp"

#include <cstddef>
#include <iostream>

#include "vec2.hpp"
#include "vec3.hpp"

double range_scale(double x, double a, double b, double c, double d) {
    return (x - a) / (b - a) * (d - c) + c;
}

double limit(double value, double min, double max) {
    return fmax(fmin(value, max), min);
}

Scene::Scene(const vec3& dimension, const vec3& camera)
        : dimension(dimension), camera(camera) {
    size_t width = this->dimension.get_y();
    size_t height = this->dimension.get_z();
    projection = new char[height * width + 1];
    projection[height * width] = '\0';
}

Scene::~Scene() { delete[] projection; }

void Scene::set_light_dir(const vec3& light_dir) {
    this->light_dir = light_dir;
    this->light_dir.norm();
}

void Scene::add_shape(Abstract_shape* shape) { shapes.push_back(shape); }

void Scene::update() {
    for (size_t idx = 0; idx < size2d(); ++idx) {
        vec2 uv{};
        size_t height = static_cast<size_t>(dimension.get_z());
        size_t width = static_cast<size_t>(dimension.get_y());
        uv.set_x(range_scale(idx % width, 0.0, width, -1.0, 1.0));
        uv.set_y(range_scale(static_cast<double>(idx) / width, 0.0, height,
                             -1.0, 1.0));
        uv *= vec2(aspect(), 1);
        vec3 temp_dir = vec3(1, uv);
        vec3 camera_dir = temp_dir.norm();
        vec2 interspection = shapes[0]->ray_interspect(camera, camera_dir);

        int color = 0;
        if (interspection.get_x() > 0) {
            vec3 it_point = camera + camera_dir * interspection.get_x();
            vec3 it_point_norm = it_point.norm();
            double diff = it_point_norm.dot_product(light_dir);
            diff = range_scale(diff, -1, 1, 0, gradient_size());
            color = limit(diff, 0, gradient_size());
        }
        char pixel = ' ';
        pixel = gradient[color];
        projection[idx] = pixel;
    }
}
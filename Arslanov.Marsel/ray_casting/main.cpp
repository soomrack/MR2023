#include <asm-generic/ioctls.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

#include "console.hpp"
#include "scene.hpp"
#include "shapes.hpp"
#include "sys/ioctl.h"
#include "vec2.hpp"
#include "vec3.hpp"

int main() {
    size_t height = 30;
    size_t width = 80;
    Console console(height, width);
    Scene scene(vec3(40, width, height), vec3(-2, 0, 0));
    scene.set_light_dir(vec3(0, 0, -1));
    Sphere sphere(vec3(0, 0, 0), 1);
    scene.add_shape(&sphere);

    console.hide_cursor();
    for (size_t frame; frame < 100000; ++frame) {
        scene.set_light_dir(vec3(sin(frame * 0.001), cos(frame * 0.001), -1));
        scene.update();
        std::cout << scene;
        console.set_cursor_start();
    }
    console.show_cursor();

    return 0;
}
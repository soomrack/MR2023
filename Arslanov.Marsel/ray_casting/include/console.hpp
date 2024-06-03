#pragma once

#include <cstddef>
#include <iostream>
#include <string>

class Console
{
private:
    size_t height{0};
    size_t width{0};

public:
    Console() = delete;
    Console(size_t height, size_t width) : height(height), width(width) {
        std::string command = "\e[8;";
        command += std::to_string(height) + ';';
        command += std::to_string(width) + 't';
        std::cout << command;
    }
    ~Console() = default;

    size_t get_height() { return height; }
    size_t get_width() { return width; }
    size_t size() { return height * width; }

    void clear() { std::cout << "\033[2J"; }

    void set_cursor(size_t col, size_t row) {
        std::string cmd = "\033[";
        cmd += std::to_string(col) + ';' + std::to_string(width) + 'H';
        std::cout << cmd;
    }

    void set_cursor_start() {
        std::cout << "\033[H";  // Установить курсор в начало консоли
    }

    void hide_cursor() { std::cout << "\033[?25l"; }

    void show_cursor() { std::cout << "\033[?25h"; }
};
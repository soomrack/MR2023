#include <stdio.h>
#include <iostream>
#include <termio.h>
#include <unistd.h>
#include <sys/select.h>

class keyboard
{
public:
    struct termios new_settings;
    struct termios init_settings;
    int key_pressed;

public:
    void init_keyboard();
    void close_keyboard();
    int scan_keyboard();    
};

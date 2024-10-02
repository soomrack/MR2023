#include "orange_bot_keydetect.hpp"


void keyboard::init_keyboard()
{
	//сохранение старых параметров терминала и ввод новых
	tcgetattr(0, &init_settings);	
	new_settings = init_settings;

	new_settings.c_lflag &= (~ICANON);	
	new_settings.c_lflag &= ~ECHO; 		
	
	new_settings.c_lflag |= ISIG; 		
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings); 
}


void keyboard::close_keyboard()
{
	//возвращение старых параметров терминала
	tcsetattr(0, TCSANOW, &init_settings); 
}


int keyboard::scan_keyboard()
{
	//получение нажатого символа
    key_pressed = getchar();
	//std::cout << key_pressed << std::endl;
	return key_pressed;
}

/*
int main(int argc, char *argv[])
{
    keyboard keyboard;
    keyboard.init_keyboard();
    while(1)
    {
        keyboard.scan_keyboard();
        printf("Key pressed: %d\n", keyboard.key_pressed);        
    }
    keyboard.close_keyboard();
}*/
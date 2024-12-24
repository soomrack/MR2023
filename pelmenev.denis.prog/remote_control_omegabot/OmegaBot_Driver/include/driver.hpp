#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <Arduino.h>
#include <Servo.h>
#include <DHT.h>
#include <math.h>

class Driver {
public:
    Driver(int left_pin, int right_pin, int left_dir_pin, int right_dir_pin, int servo_arm_pin, int servo_hand_pin, int motor_speed = 250); 
    ~Driver();
    
    void set_motors(const int velo_left, const int velo_right);
    void stop_motors();
    void drive_forward_until(const int dist);
    void connection_lost_case();
    void inspection();
    void turn_on_degree(const int degree);

    void arm(const int power);
    void hand(const int power);

    char read_command();
    void clear_serial_buffer();
    void get_command_wheels(char commad);
    void get_command_arm(char commad);
    void get_command_other(char commad);

    long int get_distance();
    double get_temperature();
    double get_humidity();
    
    void sound_signal(const int delay_time);
    
    void write_logs(char command, unsigned long time);

private:
    Servo servo_arm;
    Servo servo_hand;
    uint8_t pos_servo_arm;
    uint8_t pos_servo_hand;
    uint8_t pin_servo_arm;
    uint8_t pin_servo_hand;
    int pin_motor_left;
    int pin_motor_right;
    int pin_motor_dir_left;
    int pin_motor_dir_right;
    
private:
    char last_msg_hand;
    char previos_command;
    unsigned long previous_command_time = 0;
    int speed;
    int rotation_speed; 
    int rotation_time;          //milliseconds
};

#endif // DRIVER_HPP

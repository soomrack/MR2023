#include "driver.hpp"

#define CRITICAL_DISTANCE       30

#define SENSOR_DIST             A3
#define SENSOR_LIGHT            A1
#define AUDIO_PIN               11
#define LAMP_PIN                10

#define DHTPIN                  9
#define DHTTYPE                 DHT11

DHT dht_sensor(DHTPIN, DHTTYPE);

volatile bool LAMP_STATE   = false;
volatile bool STOP_COMMAND = false;

Driver::Driver(int left_pin, int right_pin, int left_dir_pin, int right_dir_pin, int servo_arm_pin, int servo_hand_pin, int motor_speed) 
    : pin_motor_left(left_pin), pin_motor_right(right_pin), pin_motor_dir_left(left_dir_pin), pin_motor_dir_right(right_dir_pin), speed(motor_speed), pin_servo_arm(servo_arm_pin), pin_servo_hand(servo_hand_pin)
{
    pinMode(pin_motor_left, OUTPUT);
    pinMode(pin_motor_right, OUTPUT);
    pinMode(pin_motor_dir_left, OUTPUT);
    pinMode(pin_motor_dir_right, OUTPUT);
    pinMode(SENSOR_DIST, INPUT);
    pinMode(AUDIO_PIN, OUTPUT);
    pinMode(LAMP_PIN, OUTPUT);
    dht_sensor.begin();

    servo_arm.attach(pin_servo_arm);
    servo_hand.attach(pin_servo_hand);
    pos_servo_arm   = 0;
    pos_servo_hand  = 0;
    last_msg_hand   = '0';
    previos_command = '0';
    rotation_speed  = 0.5 * speed;
    rotation_time   = 1750;

    set_motors(0, 0);
    servo_arm.write(0);
    servo_hand.write(150);
}

Driver::~Driver()
{
    set_motors(0, 0);
    servo_arm.write(0);
    servo_hand.write(150);
}

void Driver::clear_serial_buffer()
{
    while (Serial.available() > 0) {
        Serial.read();
    }
}

char Driver::read_command()
{
    char command = '0';
    auto current_time = millis();

    if (Serial.available() > 0) {
        command = Serial.read();

        if (command == '\n' || command == '\r') {
            return '0';
        }

        if (previos_command == command && (current_time - previous_command_time) <= 50) {
            clear_serial_buffer();
            return '0';
        }

        previos_command = command;
        previous_command_time = current_time;
    }

    return command;
}

void Driver::write_logs(char command, unsigned long time) 
{
    double temp = get_temperature();
    double hum  = get_humidity();
    int brightness = analogRead(SENSOR_LIGHT);
    int dist = get_distance();

    String log_msg;
    log_msg = "Time: " + String(time) + "; Command: " + String(command) + "; Distance: " + String(dist) 
            + "; Temperature: " + String(temp, 2) + "; Humidity: " + String(hum, 2) + "; Brightness: "
            + String(brightness) + " %";

    Serial.println(log_msg);
}

void Driver::sound_signal(const int delay_time)
{
    int time = delay_time;
    if (delay_time > 1000) time = 1000;
    digitalWrite(AUDIO_PIN, HIGH);
    delay(delay_time);
    digitalWrite(AUDIO_PIN, LOW);
    delay(delay_time);
}

void Driver::set_motors(const int velo_left, const int velo_right)
{
    int motor_dir_left  = (velo_left  >= 0) ? HIGH : LOW;
    int motor_dir_right = (velo_right >= 0) ? HIGH : LOW;

    digitalWrite(pin_motor_dir_left,   motor_dir_left);
    digitalWrite(pin_motor_dir_right, motor_dir_right);

    if (STOP_COMMAND) {
        analogWrite(pin_motor_left,  0);
        analogWrite(pin_motor_right, 0);
        return;
    }

    analogWrite(pin_motor_left,  constrain(abs(velo_left),  0, 255));
    analogWrite(pin_motor_right, constrain(abs(velo_right), 0, 255));
}

void Driver::stop_motors()
{
    set_motors(0, 0);
}

double Driver::get_temperature() {
    float temp = dht_sensor.readTemperature();
    if (isnan(temp)) return -1;
    return temp;
}

double Driver::get_humidity() {
    float hum = dht_sensor.readHumidity();
    if (isnan(hum)) return -1;
    return hum;
}

long int Driver::get_distance()
{
    int IR_value = analogRead(SENSOR_DIST);
    int distance = pow(10, log10(IR_value / 1821.2) / -0.65);
    if (distance <= 0) distance = 3 * CRITICAL_DISTANCE;
    return distance;
}

void Driver::drive_forward_until(const int dist)
{
    while (get_distance() > dist) {
        set_motors(speed, speed);
        if (read_command() == 's' || STOP_COMMAND) break;
    }

    stop_motors();
    sound_signal(100);
}

void Driver::connection_lost_case()
{
    stop_motors();
    sound_signal(100);

    int delay_time = 100;     // milliseconds
    int drive_time = 1500;
    int delay_counter = 0;
    int counter_limit = drive_time / delay_time;

    while (read_command() == '0' || read_command() == 'e' || delay_counter < counter_limit) {
        if (STOP_COMMAND) break;
        delay_counter++;
        set_motors(-150, -150);
        delay(delay_time);
    }

    stop_motors();

    sound_signal(50);
    sound_signal(100);
    sound_signal(200);
}

void Driver::turn_on_degree(const int degree)
{
    int millisecs = rotation_time / 360 * degree;
    int delay_counter = 0;

    set_motors(-copysign(speed, degree), copysign(speed, degree));
    while (delay_counter < millisecs) {
        if (read_command() == 's' || STOP_COMMAND) break;
        delay(1);
        delay_counter++;
    }
    stop_motors();
}

void Driver::inspection()
{
    int delay_time = 100;     // milliseconds
    int drive_time = 2000;
    int forward_counter = 0;
    int counter_limit = drive_time / delay_time;

    while (forward_counter < counter_limit) {
        set_motors(150, 150);
        if (get_distance() < CRITICAL_DISTANCE * 1.5) break;
        if (read_command() == 's' || STOP_COMMAND) break;
        delay(delay_time);
        forward_counter++;
    }

    stop_motors();
    delay(100);

    turn_on_degree(360);
    delay(100);

    int back_counter = 0;

    while (back_counter < forward_counter) {
        set_motors(-150, -150);
        if (read_command() == 's' || STOP_COMMAND) break;
        delay(delay_time);
        back_counter++;
    }

    stop_motors();
    sound_signal(100);
}

void Driver::arm(const int power)
{
    pos_servo_arm = constrain(pos_servo_arm + ((power > 0) ? 5 : -5), 0, 45);
    servo_arm.write(pos_servo_arm);
}

void Driver::hand(const int power)
{
    if (power > 0)  servo_hand.write(10);
    
    if (power <= 0) servo_hand.write(150);
}

void Driver::get_command_wheels(char command)
{
    if (command == '0') {
        stop_motors();
        return;
    }

    STOP_COMMAND = false;

    LAMP_STATE = !LAMP_STATE;
    digitalWrite(LAMP_PIN, LAMP_STATE);

    switch (command) {
        case 's':
            STOP_COMMAND = true;
            stop_motors();
            break;
        case '1':
            set_motors(speed, speed);  // Вперед
            break;
        case '2':
            set_motors(-speed, -speed);  // Назад
            break;
        case '3':
            set_motors(speed, -speed);  // Поворот вправо
            break;
        case '4':
            set_motors(-speed, speed);  // Поворот влево
            break;
        default:
            stop_motors();
            break;
    }
}

void Driver::get_command_arm(char command)
{
    if (command != '0') {
        STOP_COMMAND = false;

        LAMP_STATE = !LAMP_STATE;
        digitalWrite(LAMP_PIN, LAMP_STATE);

        switch (command) {
            case 's':
                STOP_COMMAND = true;
                stop_motors();
                break;
            case '5':
                arm(100);   // Вверх
                break;
            case '6':
                arm(-100);  // Вниз
                break;
            case '7':
                if (command != last_msg_hand) {  // Проверка только для hand()
                    hand(100);  // Сжать
                    last_msg_hand = command;
                }
                break;
            case '8':
                if (command != last_msg_hand) {  // Проверка только для hand()
                    hand(-100);  // Разжать
                    last_msg_hand = command;
                }
                break;
            default:
                break;
        }
    }
}

void Driver::get_command_other(char command)
{
    if (command != '0') {
        STOP_COMMAND = false;

        LAMP_STATE = !LAMP_STATE;
        digitalWrite(LAMP_PIN, LAMP_STATE);

        switch (command){
            case 's':
                STOP_COMMAND = true;
                stop_motors();
                break;
            case 'f':
                drive_forward_until(CRITICAL_DISTANCE);
                break;
            case 'e':
                connection_lost_case();
                break;
            case 'y':
                inspection();
                break;
            case 'o':
                turn_on_degree(360);
                break;
            default:
                break;
        }
    }
}

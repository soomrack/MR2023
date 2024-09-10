#include <Wire.h>
#include <Servo.h>
#include "mavlink.h"

// Constants for movement and grabbing
#define SPEED             110
#define SPEED_ROTATE      150
#define CRITICAL_DISTANCE 10

// I2C Address for Arduino (Slave)
#define I2C_ADDR          0x08

// Pin definitions
#define IR_PIN            A2
#define MOTOR_L_PWM_PIN   6
#define MOTOR_L_PIN       7
#define MOTOR_R_PWM_PIN   5
#define MOTOR_R_PIN       4
#define SERVO_0_PIN       9
#define SERVO_1_PIN       10

// Variables
uint8_t pos_servo_0 = 0;
uint8_t pos_servo_1 = 0;
int distance = 0;
Servo servo_0;
Servo servo_1;

// MAVLink message buffer
uint8_t mavlink_buffer[MAVLINK_MAX_PACKET_LEN];

// Define a heartbeat message
mavlink_heartbeat_t heartbeat;

// Variables to store received MAVLink command
char received_command = '\0';

// Function prototypes
void receiveEvent(int howMany);
void runForward();
void runBack();
void steerRight();
void steerLeft();
void grabUp();
void grabDown();
void grabCatch();
void grabRelease();
int readForwardRangefinder();
void stopMotors();

void setup() {
    Serial.begin(9600);

    servo_0.attach(SERVO_0_PIN);
    servo_1.attach(SERVO_1_PIN);

    pinMode(MOTOR_L_PWM_PIN, OUTPUT);
    pinMode(MOTOR_R_PWM_PIN, OUTPUT);
    pinMode(MOTOR_L_PIN, OUTPUT);
    pinMode(MOTOR_R_PIN, OUTPUT);

    Wire.begin(I2C_ADDR);
    Wire.onReceive(receiveEvent);

    heartbeat.type = MAV_TYPE_GCS;
    heartbeat.autopilot = MAV_AUTOPILOT_GENERIC;
    heartbeat.base_mode = 0;
    heartbeat.custom_mode = 0;
    heartbeat.system_status = MAV_STATE_ACTIVE;
    
    servo_0.write(0);
    servo_1.write(150);
}

void loop() {
}

void sendHeartbeat() {
    mavlink_message_t msg;
    uint16_t len;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_GCS, MAV_AUTOPILOT_GENERIC, 0, 0, MAV_STATE_ACTIVE);
    
    len = mavlink_msg_to_send_buffer(buf, &msg);
    
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(buf, len);
    Wire.endTransmission();
}

void sendDistance() {
    int distance = readForwardRangefinder();
    mavlink_message_t msg;
    uint16_t len;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    
    mavlink_msg_distance_pack(1, 200, &msg, distance);

    len = mavlink_msg_to_send_buffer(buf, &msg);
    
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(buf, len);
    Wire.endTransmission();
}





void runForward() {
    digitalWrite(MOTOR_L_PIN, HIGH);
    digitalWrite(MOTOR_R_PIN, HIGH);
    analogWrite(MOTOR_R_PWM_PIN, SPEED);
    analogWrite(MOTOR_L_PWM_PIN, SPEED);
}

void runBack() {
    digitalWrite(MOTOR_L_PIN, LOW);
    digitalWrite(MOTOR_R_PIN, LOW);
    analogWrite(MOTOR_R_PWM_PIN, SPEED);
    analogWrite(MOTOR_L_PWM_PIN, SPEED);
}

void steerRight() {
    digitalWrite(MOTOR_L_PIN, LOW);
    digitalWrite(MOTOR_R_PIN, HIGH);
    analogWrite(MOTOR_L_PWM_PIN, SPEED_ROTATE);
    analogWrite(MOTOR_R_PWM_PIN, SPEED_ROTATE);
}

void steerLeft() {
    digitalWrite(MOTOR_L_PIN, HIGH);
    digitalWrite(MOTOR_R_PIN, LOW);
    analogWrite(MOTOR_L_PWM_PIN, SPEED_ROTATE);
    analogWrite(MOTOR_R_PWM_PIN, SPEED_ROTATE);
}

void grabUp() {
    if (pos_servo_0 < 150) {
        pos_servo_0 += 6;
        servo_0.write(pos_servo_0);
        delay(50);
    }
}

void grabDown() {
    if (pos_servo_0 > 0) {
        pos_servo_0 -= 6;
        servo_0.write(pos_servo_0);
        delay(50);
    }
}

void grabCatch() {
    servo_1.write(10);
}

void grabRelease() {
    servo_1.write(150);
}

void stopMotors() {
    analogWrite(MOTOR_L_PWM_PIN, 0);
    analogWrite(MOTOR_R_PWM_PIN, 0);
}

int readForwardRangefinder() {
    int IR_value = analogRead(IR_PIN);
    int distance = pow(10, log10(IR_value / 1821.2) / -0.65);
    return distance;
}

void process_mavlink_command(uint8_t command) {
    switch (command) {
        case 'w': // Forward
            if (readForwardRangefinder() > CRITICAL_DISTANCE) {
                runForward();
            } else {
                stopMotors();
            }
            break;
        case 's': // Backward
            runBack();
            break;
        case 'a': // Left
            steerLeft();
            break;
        case 'd': // Right
            steerRight();
            break;
        case 'f': // Grab
            grabCatch();
            break;
        case 'e': // Release
            grabRelease();
            break;
        case 'o': // Grab up
            grabUp();
            break;
        case 'l': // Grab down
            grabDown();
            break;
        default:
            stopMotors();
            break;
    }
}

// I2C event handler: called when data is received via I2C
void receiveEvent(int howMany) {
    if (Wire.available() >= MAVLINK_NUM_NON_PAYLOAD_BYTES) {
        uint8_t byte;
        mavlink_message_t msg;
        mavlink_status_t status;
        while (Wire.available()) {
            byte = Wire.read();
            if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) {
                if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                    mavlink_heartbeat_t received_heartbeat;
                    mavlink_msg_heartbeat_decode(&msg, &received_heartbeat);
                    Serial.println("Received HEARTBEAT");
                } else if (msg.msgid == MAVLINK_MSG_ID_MOVE_COMMAND) {
                    mavlink_move_command_t move_command;
                    mavlink_msg_move_command_decode(&msg, &move_command);
                    process_mavlink_command(move_command.command);
                }
            }
        }
    }
}

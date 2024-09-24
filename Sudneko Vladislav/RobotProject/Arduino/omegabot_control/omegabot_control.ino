#include <Servo.h> m 
  
// Constants for movement and grabbing  
#define SPEED             110  
#define SPEED_ROTATE      150  
#define CRITICAL_DISTANCE 10  
  
// Pin definitions  
#define SENSOR_RF_FORWARD A2  
#define SENSOR_RF_LEFT    A3 
#define MOTOR_L_PWM_PIN   6  
#define MOTOR_L_PIN       7  
#define MOTOR_R_PWM_PIN   5  
#define MOTOR_R_PIN       4  
#define SERVO_0_PIN       A0  
#define SERVO_1_PIN       A1  
#define BLINK             13 
  
// Variables  
uint8_t pos_servo_0 = 0;  
uint8_t pos_servo_1 = 0;  
int distance = 0;  
Servo servo_0;  
Servo servo_1;  
  
// Function prototypes  
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
    pinMode(BLINK, INPUT);  
      
    servo_0.write(0);  
    servo_1.write(150);  
}  
  
void loop() {  
   Serial.print("Arduino: ");  
   Serial.println(readForwardRangefinder());  
    
   if (Serial.available() > 0) {  
    String input = Serial.readStringUntil('\n');  
    input.trim();  
      
    if (input.startsWith("PC:")) {  
      int commandID = input.substring(4).toInt(); 
 
      if (commandID == 22) { 
       digitalWrite(BLINK, HIGH);  
       } else { 
        digitalWrite(BLINK, LOW); 
       } 
  
      if (commandID == 22) {  
        if (readForwardRangefinder() > 10) {  
          runForward(); 
           
        }  
      } else if (commandID == 33) {  
        runBack();  
      } else if (commandID == 44) {  
        steerLeft();  
      } else if (commandID == 55) {  
        steerRight();  
      } else if (commandID == 135) { 
        if (readForwardRangefinder() > CRITICAL_DISTANCE) { 
         runForward(); 
        } else if (readLeftRangeFinder() > CRITICAl_DISTANCE) { 
           
        } 
      } 
 
      delay(100); 
    }  
  } 
   
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
    if (pos_servo_0 < 45) {  
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
 
int readLeftRangefinder() {  
    int IR_value = analogRead(SENSOR_RF_LEFT);  
    int distance = pow(10, log10(IR_value / 1821.2) / -0.65);  
    return distance;  
} 
  
int readForwardRangefinder() {  
    int IR_value = analogRead(SENSOR_RF_FORWARD);  
    int distance = pow(10, log10(IR_value / 1821.2) / -0.65);  
    return distance;  
}
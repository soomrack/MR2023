#include <Servo.h>
#include <Wire.h>

// Constants for movement and grabbing
#define SPEED              110
#define SPEED_ROTATE       150
#define CRITICAL_DISTANCE  20
#define TOLERANCE          2  // Tolerance in degrees 
                              // for stopping the rotation
#define CRITICAL_DISTANCE_FORWARD 3

// Pin definitions
#define SENSOR_RF_FORWARD  A2
#define SENSOR_RF_LEFT     A3
#define MOTOR_L_PWM_PIN    6
#define MOTOR_L_PIN        7
#define MOTOR_R_PWM_PIN    5
#define MOTOR_R_PIN        4
#define SERVO_0_PIN        A0
#define SERVO_1_PIN        A1
#define BLINK              13

#define ENCODER_K_DIST 1
#define ENCODER_K_ANGLE 2.37
unsigned long EncoderCount1, EncoderCount2;

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
unsigned long getAngleFromEnc1();
unsigned long getAngleFromEnc2();
void rotate(int targetAngle);
void runForwardUntil(int distance);
void runForwardRotateAndBack();
void runAutopilot();
void InitEnc();
void EncodersToNull();
unsigned long GetDistanceFromEnc1();
unsigned long GetDistanceFromEnc2();

void setup() {
  Serial.begin(9600);

  // Initialize servos
  servo_0.attach(SERVO_0_PIN);
  servo_1.attach(SERVO_1_PIN);

  pinMode(MOTOR_L_PWM_PIN, OUTPUT);
  pinMode(MOTOR_R_PWM_PIN, OUTPUT);
  pinMode(MOTOR_L_PIN, OUTPUT);
  pinMode(MOTOR_R_PIN, OUTPUT);
  pinMode(BLINK, INPUT);

  servo_0.write(0);
  servo_1.write(150);

  // Initialize encoders
  InitEnc();
}

void loop() {
  Serial.print("Arduino: ");
  Serial.print(readForwardRangefinder());
  Serial.print(";");
  Serial.println(readLeftRangefinder());

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("PC:")) {
      int commandID = input.substring(4).toInt();

      if (commandID == 22) {
        runForwardUntil(CRITICAL_DISTANCE_FORWARD);
      } else if (commandID == 33) {
        runBack();
      } else if (commandID == 44) {
        steerLeft();
      } else if (commandID == 55) {
        steerRight();
      } else if (commandID == 66) {
        grabCatch();
      } else if (commandID == 77) {
        grabRelease();
      } else if (commandID == 88) {
        grabUp();
      } else if (commandID == 99) {
        grabDown();
      } else if (commandID == 111) {
        stopMotors();
      } else if (commandID == 122) {
        runForwardUntil(CRITICAL_DISTANCE);
      } else if (commandID == 133) {
        runForwardRotateAndBack();
      } else if (commandID == 144) {
        runAutopilot();
      } else if (commandID == 400) {
        runBack();    
      }
      delay(10);
    }
  }
}

void runAutopilot() {
    if (readForwardRangefinder() > CRITICAL_DISTANCE) {
      runForward();
    } else if (readLeftRangefinder() > CRITICAL_DISTANCE) {
      while (!(readForwardRangefinder() > CRITICAL_DISTANCE))
        steerLeft();
    }
}

void runForwardUntil(int distance) {
    if (readForwardRangefinder() > distance) {
      runForward();
    } else {
      stopMotors();
    }
}

void runForwardRotateAndBack() {
    runForward();
    delay(5);
    rotate(360);
    runBack();
    delay(5);
}

void rotate(int targetAngle) {
    unsigned long currentAngle = (getAngleFromEnc1() + getAngleFromEnc2()) / 2;
    unsigned long angleDifference = targetAngle - currentAngle;

    while (abs(angleDifference) > TOLERANCE) {
        currentAngle = getAngleFromEnc1(); 
        angleDifference = targetAngle - currentAngle;

        if (angleDifference > 0) {
            steerRight();
        } else {
            steerLeft();
        }

        delay(50);
    }

    stopMotors();
}

unsigned long getAngleFromEnc1() {
  return (double)EncoderCount1 * (double)ENCODER_K_ANGLE;
}

unsigned long getAngleFromEnc2() {
  return (double)EncoderCount2 * (double)ENCODER_K_ANGLE;
}

void InitEnc() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, nEncoder1, CHANGE);
  attachInterrupt(1, nEncoder2, CHANGE);
}

void nEncoder1() {
  EncoderCount1++;
}

void nEncoder2() {
  EncoderCount2++;
}

void EncodersToNull() {
  EncoderCount1 = 0;
  EncoderCount2 = 0;
}

unsigned long GetDistanceFromEnc1() {
  return (double)EncoderCount1 * (double)ENCODER_K_DIST;
}

unsigned long GetDistanceFromEnc2() {
  return (double)EncoderCount2 * (double)ENCODER_K_DIST;
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

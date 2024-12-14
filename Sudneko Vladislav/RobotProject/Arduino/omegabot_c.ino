#include <Servo.h>
#include <DHT.h>

// Constants for movement and grabbing
#define SPEED              110
#define SPEED_ROTATE       150
#define CRITICAL_DISTANCE  20
#define TOLERANCE          2  // Tolerance in degrees 
                              // for stopping the rotation
#define CRITICAL_DISTANCE_FORWARD 5

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

// Настройки для датчика
#define DHTPIN 11       // Пин, к которому подключен DATA
#define DHTTYPE DHT11   // Тип датчика (DHT11)

// Создаем объект датчика
DHT dht(DHTPIN, DHTTYPE);

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
double getAngle();
void imuSetup();
void rotate(int targetAngle);
void runForwardUntil(int distance);
void runForwardRotateAndBack();
void runAutopilot();

volatile bool stopCommand = false;
volatile int prevCommand = -1;

void wait(unsigned long milliseconds) {
  if (stopCommand) return;
  unsigned long startTime = millis();
  while (millis() - startTime < milliseconds) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim();
  
      if (input.startsWith("PC:")) {
        int commandID = input.substring(4).toInt();
        if (commandID != prevCommand) {
          stopCommand = true;
          return;
          };
        }
    }
  }
}


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

  pinMode(DHTPIN, INPUT);
  dht.begin();
}

void loop() {
  Serial.print("Arduino: ");
  Serial.print(readForwardRangefinder());
  Serial.print(";");
  Serial.println(readSensor());

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("PC:")) {
      int commandID = input.substring(4).toInt();
      
      stopCommand = false;
      prevCommand = commandID;
      
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
        runForwardUntil(CRITICAL_DISTANCE_FORWARD);
      } else if (commandID == 133) {
        runForwardRotateAndBack();
      } else if (commandID == 400) {
        runAutopilot();
      }
      wait(10);
    }
  }
}

void runAutopilot() {
    runBack();
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
    wait(5000);
    steerRight();
    wait(6000);
    runBack();
    wait(5000);
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
    wait(50);
  }
}

void grabDown() {
  if (pos_servo_0 > 0) {
    pos_servo_0 -= 6;
    servo_0.write(pos_servo_0);
    wait(50);
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

float readSensor() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    return -1;
  }
  return humidity;
}

int readForwardRangefinder() {
  int IR_value = analogRead(SENSOR_RF_FORWARD);
  int distance = pow(10, log10(IR_value / 1821.2) / -0.65);
  return distance;
}

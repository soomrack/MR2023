#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIRECTION_RIGHT 4
#define DIRECTION_LEFT 7
#define SENSOR_RIGHT 1
#define SENSOR_LEFT 0

const int sensorThreshold = 800; // ~800 is tantamount to black, ~300 is tantamount to white
const int searchDelay = 100;
const int timeLimit = 10000;
const byte speedDefault = 255;

void setup() {
    pinMode(SENSOR_RIGHT, INPUT);
    pinMode(SENSOR_LEFT, INPUT);
}

void loop() {
    if ((analogRead(SENSOR_RIGHT) > sensorThreshold) && (analogRead(SENSOR_LEFT) > sensorThreshold)) forward(speedDefault);

    if ((analogRead(SENSOR_RIGHT) > sensorThreshold) && (analogRead(SENSOR_LEFT) < sensorThreshold)) right(speedDefault);

    if ((analogRead(SENSOR_RIGHT) < sensorThreshold) && (analogRead(SENSOR_LEFT) > sensorThreshold)) left(speedDefault);

    if ((analogRead(SENSOR_RIGHT) < sensorThreshold) && (analogRead(SENSOR_LEFT) < sensorThreshold)) search();
}

void forward(byte speed) {
    digitalWrite(DIRECTION_RIGHT, 1);
    digitalWrite(DIRECTION_LEFT, 1);
    analogWrite(SPEED_RIGHT, speed);
    analogWrite(SPEED_LEFT, speed);
}

void stop() {
    analogWrite(SPEED_RIGHT, 0);
    analogWrite(SPEED_LEFT, 0);
}

void left(byte speed) {
    digitalWrite(DIRECTION_RIGHT, 0);
    digitalWrite(DIRECTION_LEFT, 1);
    analogWrite(SPEED_RIGHT, 255);
    analogWrite(SPEED_LEFT, speed);
}

void right(byte speed) {
    digitalWrite(DIRECTION_RIGHT, 1);
    digitalWrite(DIRECTION_LEFT, 0);
    analogWrite(SPEED_RIGHT, speed);
    analogWrite(SPEED_LEFT, 255);
}

// void back(byte speed) {
//     digitalWrite(DIRECTION_RIGHT, 0);
//     digitalWrite(DIRECTION_LEFT, 0);
//     analogWrite(SPEED_RIGHT, speed);
//     analogWrite(SPEED_LEFT, speed);
// }

void search() {
    byte speedSearching = 100;
    int time = millis();

    while ((analogRead(SENSOR_RIGHT) < sensorThreshold) && (analogRead(SENSOR_LEFT) < sensorThreshold)) {
      if (millis() - time > timeLimit) exit(-1);
            
      delay(searchDelay);
      left(speedSearching);

      delay(searchDelay);
      forward(speedSearching);

      if (speedSearching > speedDefault) speedSearching = speedDefault;
      speedSearching += 5;

      delay(searchDelay);
    }
}
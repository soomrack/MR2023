#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIRECTION_RIGHT 4
#define DIRECTION_LEFT 7
#define SENSOR_RIGHT 1
#define SENSOR_LEFT 0


const byte PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 => 125 KHz
const byte PS_16 = (1 << ADPS2); // 16 => 1 MHz

const int threshold = 800; // ~800 is tantamount to black, ~300 is tantamount to white
const int speedDefault = 150;

void setup() {
    ADCSRA &= ~PS_128;
    ADCSRA |= PS_16;

    pinMode(SENSOR_RIGHT, INPUT);
    pinMode(SENSOR_LEFT, INPUT);
}

void loop() {
    if ((analogRead(SENSOR_RIGHT) > threshold) && (analogRead(SENSOR_LEFT) > threshold)) forward(255);

    if ((analogRead(SENSOR_RIGHT) > threshold) && (analogRead(SENSOR_LEFT) < threshold)) right(255);

    if ((analogRead(SENSOR_RIGHT) < threshold) && (analogRead(SENSOR_LEFT) > threshold)) left(255);

    if ((analogRead(SENSOR_RIGHT) < threshold) && (analogRead(SENSOR_LEFT) < threshold)) search();
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

void back(byte speed) {
    digitalWrite(DIRECTION_RIGHT, 0);
    digitalWrite(DIRECTION_LEFT, 0);
    analogWrite(SPEED_RIGHT, speed);
    analogWrite(SPEED_LEFT, speed);
}

void search() {
    byte speedIncrement = 100;

    while ((analogRead(SENSOR_RIGHT) < threshold) && (analogRead(SENSOR_LEFT) < threshold)) {
        delay(100);
        left(speedDefault);

        delay(100);
        forward(speedIncrement);

        if (speedIncrement > speedDefault) speedIncrement = speedDefault;

        speedIncrement += 1;
        delay(100);
    }
}
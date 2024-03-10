#define PIN_SPEED_R 5
#define PIN_SPEED_L 6
#define PIN_DIR_R 4
#define PIN_DIR_L 7

#define PIN_SENSOR_R 1
#define PIN_SENSOR_L 0

#define PIN_BUZZER 8


const byte SPEED_DEFAULT = 255;

const int SENSOR_THRESHOLD = 800; 

const int TIME_DELAY = 100;  
const int TIME_LIMIT = 10000; 


void setup() {
  pinMode(PIN_SENSOR_R, INPUT);
  pinMode(PIN_SENSOR_L, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}


void loop() {
  if ((analogRead(PIN_SENSOR_R) > SENSOR_THRESHOLD) && 
      (analogRead(PIN_SENSOR_L) > SENSOR_THRESHOLD)) 
        move_forward(SPEED_DEFAULT);

  if ((analogRead(PIN_SENSOR_R) > SENSOR_THRESHOLD) && 
    (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) 
        turn_right(SPEED_DEFAULT);

  if ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && 
    (analogRead(PIN_SENSOR_L) > SENSOR_THRESHOLD)) 
        turn_left(SPEED_DEFAULT);

  if ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && 
    (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) 
      search();
}


void move_forward(byte speed) {
  digitalWrite(PIN_DIR_R, 1);
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_R, speed);
  analogWrite(PIN_SPEED_L, speed);
}

void move_backward(byte speed) {
    digitalWrite(PIN_DIR_R, 0);
    digitalWrite(PIN_DIR_L, 0);
    analogWrite(PIN_SPEED_R, speed);
    analogWrite(PIN_SPEED_L, speed);
}

void turn_left(byte speed) {
    digitalWrite(PIN_DIR_R, 0);
    digitalWrite(PIN_DIR_L, 1);
    analogWrite(PIN_SPEED_R, 255);
    analogWrite(PIN_SPEED_L, speed);
}

void turn_right(byte speed) {
    digitalWrite(PIN_DIR_R, 1);
    digitalWrite(PIN_DIR_L, 0);
    analogWrite(PIN_SPEED_R, speed);
    analogWrite(PIN_SPEED_L, 255);
}


void search() {
    byte speedSearching = 100;
    int time = millis();

    while ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) {
      if (millis() - time > TIME_LIMIT) {
        analogWrite(PIN_SPEED_R, 0);
        analogWrite(PIN_SPEED_L, 0);

        digitalWrite(PIN_BUZZER, 1);
        delay(2000);
        digitalWrite(PIN_BUZZER, 0);

        exit(1);
      }
            
      delay(TIME_DELAY);
      turn_left(speedSearching);

      delay(TIME_DELAY);
      move_forward(speedSearching);

      delay(TIME_DELAY);
    }
}
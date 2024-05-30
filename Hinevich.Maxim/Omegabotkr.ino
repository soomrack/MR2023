#define SPEED_LEFT 5
#define SPEED_RIGHT 6
#define DIR_LEFT 4
#define DIR_RIGHT 7
#define LEFT_ULTRASONIC_TRIG_PIN 8
#define LEFT_ULTRASONIC_ECHO_PIN 9
#define FRONT_ULTRASONIC_TRIG_PIN 10
#define FRONT_ULTRASONIC_ECHO_PIN 11
#define SOUND_PIN 12
#define State_FORWARD 0
#define State_RIGHT 1
#define State_LEFT 2
#define State_FIND 3
#define MAX_ROTATION_SPEED 250
#define MAX_MOVE_SPEED 180
#define MIN_ROTATION_SPEED 200
#define MIN_MOVE_SPEED 150
#define SPEED_STEP 2

int current_speed = 0;
int State, TargetState;
unsigned long timer;

void move(bool left_direction, bool right_direction, uint8_t left_speed, uint8_t right_speed) {
  analogWrite(SPEED_LEFT, left_speed);
  analogWrite(SPEED_RIGHT, right_speed);
  digitalWrite(DIR_LEFT, left_direction);
  digitalWrite(DIR_RIGHT, right_direction);
}

void forward() {
  digitalWrite(SOUND_PIN, 0);
  timer = millis();
  if (State == State_FORWARD && current_speed + SPEED_STEP >= MAX_MOVE_SPEED) 
    current_speed = MAX_MOVE_SPEED;
  else if (State == State_FORWARD) 
    current_speed += SPEED_STEP;
  else {
    State = State_FORWARD;
    current_speed = MIN_MOVE_SPEED;
  }
  move(1, 1, current_speed, current_speed);
}

void right() {
  State = State_RIGHT;
  timer = millis();
  digitalWrite(SOUND_PIN, 0);
  move(1, 0, MAX_ROTATION_SPEED, MIN_ROTATION_SPEED);
}

void left() {
  State = State_LEFT;
  timer = millis();
  digitalWrite(SOUND_PIN, 0);
  move(0, 1, MIN_ROTATION_SPEED, MAX_ROTATION_SPEED);
}

void find() {
  if (State != State_FIND) timer = millis();
  State = State_FIND;
  if ((millis() - timer) > 5000) {
    digitalWrite(SOUND_PIN, 1);
    move(1, 1, 0, 0);
  } else {
    move(1, 1, 100, 100);
    delay(100);
    move(1, 0, 100, 100);
    delay(100);
  }
}

long readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(FRONT_ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(FRONT_ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(SPEED_LEFT, OUTPUT);
  pinMode(SPEED_RIGHT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
}

void loop() {
  long left_distance = readUltrasonicDistance(LEFT_ULTRASONIC_TRIG_PIN, LEFT_ULTRASONIC_ECHO_PIN);
  long front_distance = readUltrasonicDistance(FRONT_ULTRASONIC_TRIG_PIN, FRONT_ULTRASONIC_ECHO_PIN);

  if (front_distance > 20 && left_distance < 15) {
    TargetState = State_FORWARD;
  } else if (front_distance <= 20) {
    TargetState = State_RIGHT;
  } else if (left_distance >= 15) {
    TargetState = State_LEFT;
  } else {
    TargetState = State_FIND;
  }

  switch (TargetState) {
    case State_FORWARD: 
      forward(); 
      break;
    case State_RIGHT: 
      right(); 
      break;
    case State_LEFT: 
      left(); 
      break;
    case State_FIND: 
      find(); 
      break;
  }
}

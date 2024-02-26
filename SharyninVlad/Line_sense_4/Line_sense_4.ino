#define SPEED_LEFT 5
#define SPEED_RIGHT 6
#define DIR_LEFT 4
#define DIR_RIGHT 7

#define LEFT_SENSOR_PIN A2
#define RIGHT_SENSOR_PIN A3
#define SOUND_PIN 10

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

void Move(bool Left_direction, bool Right_direction, uint8_t Left_speed, uint8_t Right_speed) {
  analogWrite(SPEED_LEFT, Left_speed);
  analogWrite(SPEED_RIGHT, Right_speed);
  digitalWrite(DIR_LEFT, Left_direction);
  digitalWrite(DIR_RIGHT, Right_direction);
}

void Forward() {
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
  Move(1, 1, current_speed, current_speed);
}

void Right() {
  State = State_RIGHT;
  timer = millis();
  digitalWrite(SOUND_PIN, 0);
  Move(1, 0, MAX_ROTATION_SPEED, MIN_ROTATION_SPEED);
}

void Left() {
  State = State_LEFT;
  timer = millis();
  digitalWrite(SOUND_PIN, 0);
  Move(0, 1, MIN_ROTATION_SPEED, MAX_ROTATION_SPEED);
}

void Find_line() {
  if (State != State_FIND) timer = millis();
  State = State_FIND;
  if ((millis() - timer) > 5000) {
    digitalWrite(SOUND_PIN, 1);
    Move(1, 1, 0, 0);
  } else {
    Move(1, 1, 100, 100);
    delay(100);
    Move(1, 0, 100, 100);
    delay(100);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  pinMode(SPEED_LEFT, OUTPUT);
  pinMode(SPEED_RIGHT, OUTPUT);

  pinMode(DIR_LEFT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
}

void loop() {
  boolean left_sensor, right_sensor;

  if (analogRead(LEFT_SENSOR_PIN) > 600) left_sensor = 1;
  else left_sensor = 0;
  if (analogRead(RIGHT_SENSOR_PIN) > 600) right_sensor = 1;
  else right_sensor = 0;

  if (left_sensor == 1 && right_sensor == 1) TargetState = State_FORWARD;
  else if (left_sensor == 1 && right_sensor == 0) TargetState = State_LEFT;
  else if (left_sensor == 0 && right_sensor == 1) TargetState = State_RIGHT;
  else TargetState = State_FIND;
  //Serial.println(TargetState);

  //Serial.println(State);

  switch (TargetState) {
    case State_FORWARD:
      Forward();
      break;
    case State_RIGHT:
      Right();
      break;
    case State_LEFT:
      Left();
      break;
    case State_FIND:
      Find_line();
      break;
  }
}
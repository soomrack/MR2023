#define LEFT_MOTOR_A  11
#define LEFT_MOTOR_B  10

#define RIGHT_MOTOR_A  5
#define RIGHT_MOTOR_B  3

unsigned long currentTime = millis();
unsigned long previousTime = millis();

void drive(int left_pwm, int right_pwm)
{
  if (left_pwm >= 0) {
    digitalWrite(LEFT_MOTOR_A, 1);
    analogWrite(LEFT_MOTOR_B, 255 - left_pwm);
  }
  else {
    left_pwm = -left_pwm;
    digitalWrite(LEFT_MOTOR_B, 1);
    analogWrite(LEFT_MOTOR_A, 255 - left_pwm);
  }

  if (right_pwm >= 0) {
    digitalWrite(RIGHT_MOTOR_A, 1);
    analogWrite(RIGHT_MOTOR_B, 255 - right_pwm);
  }
  else {
    right_pwm = -right_pwm;
    digitalWrite(RIGHT_MOTOR_B, 1);
    analogWrite(RIGHT_MOTOR_A, 255 - right_pwm);
  }
}

void setup() {
  Serial.begin(19200);
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);
}

void loop() {
  currentTime = millis();

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');

    if (commaIndex > 0) {
      int left_pwm = data.substring(0, commaIndex).toInt();
      int right_pwm = data.substring(commaIndex + 1).toInt();
      /*
      Serial.print("L: ");
      Serial.print(left_pwm);
      Serial.print("  R: ");
      Serial.println(right_pwm);
     */
      drive(left_pwm, right_pwm);

      previousTime = millis();
    }
  }
  else if (currentTime - previousTime > 500) drive(0, 0);
}

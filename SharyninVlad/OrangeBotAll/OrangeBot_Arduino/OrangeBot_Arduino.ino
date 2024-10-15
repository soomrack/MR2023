#define LEFT_MOTOR_A  11
#define LEFT_MOTOR_B  10

#define RIGHT_MOTOR_A  5
#define RIGHT_MOTOR_B  3

#define US_TRIG_PIN 7
#define US_ECHO_PIN 8

#define SOUND_SENS_PIN A1

unsigned long currentTime = millis();
unsigned long previousTime = millis();
unsigned long PrTime = millis();
int timeflag = 1;
long distance_to_object;

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


void send_distance_to_object(unsigned long Time) 
{
  long duration, distance_cm;

  if (timeflag == 1)
  {
    digitalWrite(US_TRIG_PIN, LOW);
    timeflag = 2;
  }

  if (Time - PrTime >= 2 && timeflag == 2)
  {
    digitalWrite(US_TRIG_PIN, HIGH);
    timeflag = 3;
  }

  if (Time - PrTime >= 12 && timeflag == 3)
  {
    digitalWrite(US_TRIG_PIN, LOW);
    timeflag = 1;
    PrTime = Time;
    // Засекаем время возвращения сигнала
    duration = pulseIn(US_ECHO_PIN, HIGH, 30000);  // 30 ms тайм-аут
    distance_cm = duration * 0.034 / 2;

    if (distance_cm <= 0 || distance_cm > 60)
      distance_cm = 60;
    Serial.println(distance_cm);
  }
}


void send_sound_info() {
  int sound_level = digitalRead(SOUND_SENS_PIN);
  
  Serial.println(sound_level + 70);
}


void setup() {
  Serial.begin(19200);
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  pinMode(SOUND_SENS_PIN, INPUT);
}

void loop() {
  currentTime = millis();

  ///send distance to orange
  send_distance_to_object(currentTime);
  send_sound_info();
  
  //Serial.println(currentTime);
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');

    if (commaIndex > 0) {
      int left_pwm = data.substring(0, commaIndex).toInt();
      int right_pwm = data.substring(commaIndex + 1).toInt();
      int status = data.substring(commaIndex + 2).toInt();
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

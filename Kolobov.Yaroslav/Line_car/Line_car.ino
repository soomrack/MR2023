#define SENS_L A1
#define SENS_R A2
#define MOTOR_L_DIR 7
#define MOTOR_R_DIR 4
#define MOTOR_L_SPEED 6
#define MOTOR_R_SPEED 5
#define SAS A0


void forward(int speed) {
  digitalWrite(MOTOR_L_DIR, HIGH);
  digitalWrite(MOTOR_R_DIR, HIGH);
  analogWrite(MOTOR_L_SPEED, speed);
  analogWrite(MOTOR_R_SPEED, speed);
}


void left(int speed_1, int speed_2) {
  digitalWrite(MOTOR_L_DIR, LOW);
  digitalWrite(MOTOR_R_DIR, HIGH);
  analogWrite(MOTOR_L_SPEED, speed_2);
  analogWrite(MOTOR_R_SPEED, speed_1);
}

void right(int speed_1, int speed_2) {
  digitalWrite(MOTOR_L_DIR, HIGH);
  digitalWrite(MOTOR_R_DIR, LOW);
  analogWrite(MOTOR_L_SPEED, speed_1);
  analogWrite(MOTOR_R_SPEED, speed_2);
}


void back(int speed) {
  digitalWrite(MOTOR_L_DIR, LOW);
  digitalWrite(MOTOR_R_DIR, LOW);
  analogWrite(MOTOR_L_SPEED, speed);
  analogWrite(MOTOR_R_SPEED, speed);
}

void forward_look(int speed) {
  digitalWrite(MOTOR_L_DIR, HIGH);
  digitalWrite(MOTOR_R_DIR, HIGH);
  analogWrite(MOTOR_L_SPEED, speed);
  analogWrite(MOTOR_R_SPEED, speed);
}


void stop() {
  digitalWrite(MOTOR_L_DIR, HIGH);
  digitalWrite(MOTOR_R_DIR, HIGH);
  analogWrite(MOTOR_L_SPEED, 0);
  analogWrite(MOTOR_R_SPEED, 0);
}


void path_finding() {
  int speed = 100;
  unsigned long time = millis();

  while (analogRead(SENS_L) < 700 && analogRead(SENS_R) < 700) {
  left(180, 150);
  delay(100);
  forward_look(speed);
  delay(60);

  speed = speed + 2;

  if (speed >= 170) {speed = 170;}
  delay(100);

  if (millis() - time > 5000)
  {
    stop();
    analogWrite(SAS, 255);
    delay(7000);
  }
  }

}


void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_L_SPEED, OUTPUT);
  pinMode(MOTOR_L_DIR, OUTPUT);
  pinMode(MOTOR_R_SPEED, OUTPUT);
  pinMode(MOTOR_R_DIR, OUTPUT);
}


void loop() {
  int sens_l = analogRead(SENS_L);
  int sens_r = analogRead(SENS_R);

  // Serial.println(sens_l);
  // Serial.println(sens_r);
  // Serial.println();

  if (sens_l > 800 && sens_r > 800) {forward(255);}
  else if (sens_l > 800 && sens_r < 800) {left(230, 160);}
  else if (sens_r > 800 && sens_l < 800) {right(230, 160);}
  //if (sens_l < 800 && sens_r < 800) {path_finding();}
  else {path_finding();}


}

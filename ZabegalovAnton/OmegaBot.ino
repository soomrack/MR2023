#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
#define LIGHT_RIGHT A2
#define LIGHT_LEFT A1
#define SOS A0

int Light = 800;
int speed_80 = 240;
int time;

void InitMotors()
{
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
}

void Motors (int Speed1, int Speed2)
{
  if (Speed1 > 255) Speed1 = 255;
  if (Speed1 < -255) Speed1 = -255;
  if (Speed2 > 255) Speed2 = 255;
  if (Speed2 < -255) Speed2 = -255;

  if (Speed1 > 0) {
    digitalWrite(M1_DIR, 1);
    analogWrite(M1_PWM, Speed1); 
  } else {
    digitalWrite(M1_DIR, 0);
    analogWrite(M1_PWM, -Speed1);
  }

  if (Speed2 > 0) {
    digitalWrite(M2_DIR, 1);
    analogWrite(M2_PWM, Speed2); 
  } else {
    digitalWrite(M2_DIR, 0);
    analogWrite(M2_PWM, -Speed2);
  }
}

void forward()
{
  Motors(240, 240);
}

void Leftforward()
{
  Motors (240, -110);
}

void rightforward()
{
  Motors (-110, 240);
}

void Stop()
{
  Motors(0, 0);
} 

void MoveBack(int Speed)
{
  Motors(-Speed, -Speed);
}

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_RIGHT, INPUT);
  pinMode(LIGHT_LEFT, INPUT);

  pinMode(SOS, OUTPUT);

  InitMotors();
}

void loop() {
  Serial.println(analogRead(LIGHT_RIGHT));
  Serial.println(analogRead(LIGHT_LEFT));
  Serial.println();
  if ((analogRead(LIGHT_RIGHT) > Light) && (analogRead(LIGHT_LEFT) > Light)) {
    forward();
  } else if ((analogRead(LIGHT_RIGHT) > Light) && (analogRead(LIGHT_LEFT) < Light)){
    rightforward();
  } else if ((analogRead(LIGHT_RIGHT) < Light) && (analogRead(LIGHT_LEFT) > Light)){
    Leftforward();  
  } 
  
  if ((analogRead(LIGHT_RIGHT) < Light) && (analogRead(LIGHT_LEFT) < Light)){
    delay(1000); 
    Stop();
    time = millis();
    while ((analogRead(LIGHT_RIGHT) < Light) && (analogRead(LIGHT_LEFT) < Light)){ 
      speed_80--;
      Motors(80, speed_80);
      if (millis() - time >= 7000){
        Stop();
        analogWrite(SOS, 255);
        delay(1000);
        analogWrite(SOS, 0);
        while(true){
          Stop();
        }
      }
    }
  }
}

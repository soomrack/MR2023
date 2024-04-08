#define PIN_DIR_L 7  
#define PIN_DIR_R 4 

#define PIN_SPEED_L 6 
#define PIN_SPEED_R 5 

#define PIN_LIGHT_L A0 
#define PIN_LIGHT_R A1

#define PIN_SOUND A2 

#define BLACK 800 

void setup() 
{
  pinMode(PIN_DIR_R, OUTPUT);
  pinMode(PIN_SPEED_R, OUTPUT);
  pinMode(PIN_SPEED_L, OUTPUT);
  pinMode(PIN_DIR_L, OUTPUT);

  Serial.begin(9600);
}

void forward(int speed)
{
  digitalWrite(PIN_DIR_R, 1);
  analogWrite(PIN_SPEED_R, speed);
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_L, speed);
}

void backward() 
{
  digitalWrite(PIN_DIR_R, 0);
  analogWrite(PIN_SPEED_R, 100);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_L, 100);
}

void alt_r() 
{
  digitalWrite(PIN_DIR_R, 1);
  analogWrite(PIN_SPEED_R, 255);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_L, 130);
  
}

void alt_l() 
{
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_L, 255);
  digitalWrite(PIN_DIR_R, 0);
  analogWrite(PIN_SPEED_R, 130);
  
}

void stop() 
{
  while(analogRead(PIN_LIGHT_R) < BLACK && analogRead(PIN_LIGHT_L) < BLACK){
    analogWrite(PIN_SPEED_R, 0);
    analogWrite(PIN_SPEED_L, 0);
  }
}

void not_found()
{
  analogWrite(PIN_SPEED_R, 0);
  analogWrite(PIN_SPEED_L, 0);
  analogWrite(PIN_SOUND, 255);
  delay(1500);
  analogWrite(PIN_SOUND, 0);
  stop();
}

void turnaround(int speed)
{
  digitalWrite(PIN_DIR_R, 1);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_R, speed);
  analogWrite(PIN_SPEED_L, speed);
}

void find()
{
  int idx = 0;
  int speed = 70;
  unsigned long time = 0;
  while(true){
    time += 200;
    idx = idx + 1;
    speed = speed + 2;
    if (time > 5000){not_found();}
    delay(200);
      if (analogRead(PIN_LIGHT_R) > BLACK || analogRead(PIN_LIGHT_L) > BLACK){break;}
      if (idx % 2 == 0){forward(speed);} else {turnaround(180);}
  }
}

void loop()
{
  if (analogRead(PIN_LIGHT_L) > BLACK && analogRead(PIN_LIGHT_R) > BLACK){forward(200);}
  if (analogRead(PIN_LIGHT_L) > BLACK && analogRead(PIN_LIGHT_R) < BLACK){alt_r();}
  if (analogRead(PIN_LIGHT_L) < BLACK && analogRead(PIN_LIGHT_R) > BLACK){alt_l();}
  if (analogRead(PIN_LIGHT_L) < BLACK && analogRead(PIN_LIGHT_R) < BLACK){find();}
  //light_sensor();
}

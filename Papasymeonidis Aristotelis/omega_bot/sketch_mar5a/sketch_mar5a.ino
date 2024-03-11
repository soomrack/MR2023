#define PIN_DIR_L 7  
#define PIN_DIR_R 4 

#define PIN_SPEED_L 6 
#define PIN_SPEED_R 5 

#define PIN_LIGHT_L A0 
#define PIN_LIGHT_R A1

#define PIN_SOUND A3 

#define BLACK 800 

void setup() 
{
  pinMode(PIN_DIR_R, OUTPUT);
  pinMode(PIN_SPEED_R, OUTPUT);
  pinMode(PIN_SPEED_L, OUTPUT);
  pinMode(PIN_DIR_L, OUTPUT);

  Serial.begin(9600);
}

void light_sensor() 

{
  Serial.println(analogRead(A0));
  delay(200);
}

void drive(int speed)
{
  digitalWrite(PIN_DIR_R, 1);
  analogWrite(PIN_SPEED_R, speed);
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_L, speed);
}

void revers() 
{
  digitalWrite(PIN_DIR_R, 0);
  analogWrite(PIN_SPEED_R, 100);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_L, 100);
}

void correct_r() 
{
  digitalWrite(PIN_DIR_R, 1);
  analogWrite(PIN_SPEED_R, 255);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_L, 130);
  
}

void correct_l() 
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

void dead_end()
{
  analogWrite(PIN_SPEED_R, 0);
  analogWrite(PIN_SPEED_L, 0);
  analogWrite(PIN_SOUND, 255);
  delay(1500);
  analogWrite(PIN_SOUND, 0);
  stop();
}

void right_turn(int speed) // turn in right direction
{
  digitalWrite(PIN_DIR_R, 1);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_R, speed);
  analogWrite(PIN_SPEED_L, speed);
}

void total_correct() // line search function
{
  int idx = 0;
  int speed = 70;
  unsigned long time = 0; // переменная отсчитывающая время до остановки в следствии невозможности найти линию
  while(true){
    time += 200;
    idx = idx + 1;
    speed = speed + 2;
    if (time > 5000){dead_end();}
    delay(200);
      if (analogRead(PIN_LIGHT_R) > BLACK || analogRead(PIN_LIGHT_L) > BLACK){break;}
      if (idx % 2 == 0){drive(speed);} else {right_turn(180);}
  }
}

void loop() // main function checking whether it is on the line
{
  if (analogRead(PIN_LIGHT_L) > BLACK && analogRead(PIN_LIGHT_R) > BLACK){drive(200);} // вызывает езду по прямой вследствии нахождения обоих датчиков на линии
  if (analogRead(PIN_LIGHT_L) > BLACK && analogRead(PIN_LIGHT_R) < BLACK){correct_r();} // корректировка положения робота при вхождении в поворот
  if (analogRead(PIN_LIGHT_L) < BLACK && analogRead(PIN_LIGHT_R) > BLACK){correct_l();} // корректировка положения робота при вхождении в поворот
  if (analogRead(PIN_LIGHT_L) < BLACK && analogRead(PIN_LIGHT_R) < BLACK){total_correct();} // поиск линии вследствии потери ее обоими датчиками 
  //light_sensor();
}

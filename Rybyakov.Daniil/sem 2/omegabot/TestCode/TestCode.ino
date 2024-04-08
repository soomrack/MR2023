#define DIR_L 7 // left wheel rotation direction 
#define DIR_R 4 // right wheel rotation direction
#define SPEED_L 6 // left wheel rotation speed 
#define SPEED_R 5 // right wheel rotation speed
#define LIGHT_L A0 // values from left light sensor
#define LIGHT_R A1 // values from right light sensor
#define SOUND A3 // signalization 
#define BLACK 800 // value of black color

// rotation speed of wheels changes from 0 to 255 (80 - 255)
// for light sensors 0 - 400 is white, >800 is black

void setup() // activation of nedeed pins
{
  pinMode(DIR_R, OUTPUT);
  pinMode(SPEED_R, OUTPUT);
  pinMode(SPEED_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  Serial.begin(9600);
}

void light_sensor() // output of light sensor's value  
{
  Serial.println(analogRead(A0));
  delay(200);
}

void drive(int speed) // driving in forward direction
{
  digitalWrite(DIR_R, 1);
  analogWrite(SPEED_R, speed);
  digitalWrite(DIR_L, 1);
  analogWrite(SPEED_L, speed);
}

void revers() // driving in revers direction
{
  digitalWrite(DIR_R, 0);
  analogWrite(SPEED_R, 100);
  digitalWrite(DIR_L, 0);
  analogWrite(SPEED_L, 100);
}

void correct_r() // left turn or correction of rigth wheel position
{
  digitalWrite(DIR_R, 1);
  analogWrite(SPEED_R, 255);
  digitalWrite(DIR_L, 0);
  analogWrite(SPEED_L, 130);
  // вращение второго колесса в обратной направлении для более эффеткивного поворота
}

void correct_l() // right turn or correction of left wheel position
{
  digitalWrite(DIR_L, 1);
  analogWrite(SPEED_L, 255);
  digitalWrite(DIR_R, 0);
  analogWrite(SPEED_R, 130);
  // вращение второго колесса в обратной направлении для более эффеткивного поворота
}

void stop() // stopping wheels rotation
{
  while(analogRead(LIGHT_R) < BLACK && analogRead(LIGHT_L) < BLACK){
    analogWrite(SPEED_R, 0);
    analogWrite(SPEED_L, 0);
  }
}

void dead_end() // situation when bot can't fing the line
{
  analogWrite(SPEED_R, 0);
  analogWrite(SPEED_L, 0);
  analogWrite(SOUND, 255);
  delay(1500);
  analogWrite(SOUND, 0);
  stop();
}

void right_turn(int speed) // turn in right direction
{
  digitalWrite(DIR_R, 1);
  digitalWrite(DIR_L, 0);
  analogWrite(SPEED_R, speed);
  analogWrite(SPEED_L, speed);
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

      if (analogRead(LIGHT_R) > BLACK || analogRead(LIGHT_L) > BLACK){break;}
      if (idx % 2 == 0){drive(speed);} else {right_turn(180);}
  }
}

void loop() // main function checking whether it is on the line
{
  if (analogRead(LIGHT_L) > BLACK && analogRead(LIGHT_R) > BLACK){drive(200);} // вызывает езду по прямой вследствии нахождения обоих датчиков на линии
  if (analogRead(LIGHT_L) > BLACK && analogRead(LIGHT_R) < BLACK){correct_r();} // корректировка положения робота при вхождении в поворот
  if (analogRead(LIGHT_L) < BLACK && analogRead(LIGHT_R) > BLACK){correct_l();} // корректировка положения робота при вхождении в поворот
  if (analogRead(LIGHT_L) < BLACK && analogRead(LIGHT_R) < BLACK){total_correct();} // поиск линии вследствии потери ее обоими датчиками 
  //light_sensor();
}
 #define Left_D 7
 #define Left_A 6
 #define Right_D 4
 #define Right_A 5
 #define Right_sens A2
 #define Left_sens A3
 #define SOS 8

void setup() 
{
  pinMode(Left_D, OUTPUT);
  pinMode(Left_A, OUTPUT);
  pinMode(Right_D, OUTPUT);
  pinMode(Right_A, OUTPUT);
  pinMode(SOS, OUTPUT);
}

void forward(int speed)
  {
    digitalWrite(Left_D, HIGH);
    analogWrite(Left_A, speed);
    digitalWrite(Right_D, HIGH);
    analogWrite(Right_A, speed);
  }

void right(int speed)
{
  digitalWrite(Left_D, HIGH);
  analogWrite(Left_A, speed);
  digitalWrite(Right_D, LOW); 
  analogWrite(Right_A, 180);
}

void left(int speed)
{
  digitalWrite(Left_D, LOW); 
  analogWrite(Left_A, 180);
  digitalWrite(Right_D, HIGH);
  analogWrite(Right_A, speed); 
}

void stop()
{
  digitalWrite(Left_D, HIGH); 
  analogWrite(Left_A, 0);
  digitalWrite(Right_D, HIGH);
  analogWrite(Right_A, 0);
}

void drive(int speed)
{
  int blackColor = 820;
  int leftIndicator = analogRead(Left_sens);
  int rightIndicator = analogRead(Right_sens);

  if ((leftIndicator >= blackColor) && (rightIndicator >= blackColor))
  {
    forward(speed);
  }
  else if ((leftIndicator < blackColor) && (rightIndicator >= blackColor))
  {
    right(speed);
  }
  else if ((leftIndicator >= blackColor) && (rightIndicator < blackColor))
  {
    left(speed);
  }
  else 
  {
    found(speed);
  } 
  
}

void found(int speed)
{
  unsigned long time = millis(); 
  int foundSpeed = 100;

  while ((analogRead(Left_sens) < 800) && (analogRead(Right_sens) < 800)) 
  {  
    right(foundSpeed); 
    delay(100); 
    forward(foundSpeed); 
    delay(100);

    foundSpeed += 2;

    if (foundSpeed > 240)
    { 
      foundSpeed = 100; 
    } 

    if (millis() - time > 7000)
    { 
      stop();
      digitalWrite(SOS, HIGH);
      delay(5000);
    }
  }

  int leftIndicator = analogRead(Left_sens);
  int rightIndicator = analogRead(Right_sens);

  if ((leftIndicator >= 800) && (rightIndicator >= 800))
  {
    right(speed);
    delay(500);
  }
}

void loop() 
{
  drive(244);
}

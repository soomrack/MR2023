#define SPEED_R         5
#define SPEED_L         6
#define DIR_R           4
#define DIR_L           7
#define LIGHT_RIGHT     1
#define LIGHT_LEFT      0
#define SOUND           8


int light_mem = 0;


void setup() 
{
  Serial.begin(9600);
  pinMode(LIGHT_RIGHT, INPUT);
  pinMode(LIGHT_LEFT, INPUT);
  pinMode(SOUND, OUTPUT);

  while (1) {
    if ((binarize(analogRead(LIGHT_LEFT)) == 1) && (binarize(analogRead(LIGHT_RIGHT)) == 1))
      forward(255);
    
    if ((binarize(analogRead(LIGHT_LEFT)) == 1) && (binarize(analogRead(LIGHT_RIGHT)) == 0))
      turn(0, 1, 255);
    
    if ((binarize(analogRead(LIGHT_LEFT)) == 0) && (binarize(analogRead(LIGHT_RIGHT)) == 1))
      turn(1, 0, 255);

    if ((binarize(analogRead(LIGHT_LEFT)) == 0) && (binarize(analogRead(LIGHT_RIGHT)) == 0))
      find_way();

    light_mem = binarize(analogRead(LIGHT_LEFT));

    delay(5);
  }  
}


void loop() {}


int binarize(int detect)
{
  if (detect >= 800) return 1;
  else return 0;
}


void forward(int spd)
{
  digitalWrite(DIR_R, HIGH);
  digitalWrite(DIR_L, HIGH);

  analogWrite(SPEED_R, spd);
  analogWrite(SPEED_L, spd);
}


void turn(int right, int left, int spd)
{
  if ((right == 1) && (left == 0)) {
    digitalWrite(DIR_R, LOW);
    digitalWrite(DIR_L, HIGH);
  } else if ((right == 0) && (left == 1)) {
    digitalWrite(DIR_R, HIGH);
    digitalWrite(DIR_L, LOW);
  }

  analogWrite(SPEED_R, spd);
  analogWrite(SPEED_L, spd);
}


void stop() { 
  analogWrite(SPEED_R, LOW);
  analogWrite(SPEED_L, LOW);
  
  while (true) {
    digitalWrite(SOUND, HIGH);

    if ((binarize(analogRead(LIGHT_LEFT)) == 1) && (binarize(analogRead(LIGHT_RIGHT)) == 1)) {
      digitalWrite(SOUND, LOW);
      break;
    }

    delay(300);
    
    digitalWrite(SOUND, LOW);
    delay(300);
  };
} 


void find_way()
{
  unsigned long time = millis();
  int speed_increment = 100;

  while ((binarize(analogRead(LIGHT_LEFT)) == 0) && (binarize(analogRead(LIGHT_RIGHT)) == 0)) {
    delay(100);
    turn(!light_mem, light_mem, 150);
    delay(100);
    forward(speed_increment);

    if (speed_increment > 150) { 
      speed_increment = 150; 
    }

    speed_increment += 1;

    if (millis() - time > 7000) {
      stop();
      break;
    }

    delay(100);
  }
}
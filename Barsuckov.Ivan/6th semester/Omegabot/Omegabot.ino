#define PIN_SPEED_RIGHT 5
#define PIN_SPEED_LEFT 6
#define PIN_RIGHT_DIRECTION 4
#define PIN_LEFT_DIRECTION 7 
#define PIN_LIGHT_RIGHT 1
#define PIN_LIGHT_LEFT 0
#define PIN_SOUND 8


const byte PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
const byte PS_16 = (1 << ADPS2); 


void setup() {
    
    ADCSRA &= ~PS_128; 
    ADCSRA |= PS_16; 

    pinMode(PIN_LIGHT_RIGHT, INPUT); 
    pinMode(PIN_LIGHT_LEFT, INPUT); 
    pinMode(PIN_SOUND, OUTPUT);
    int freshold = 800; 
    
    while (true) {
        if ((analogRead(PIN_LIGHT_RIGHT) > freshold)  &&  (analogRead(PIN_LIGHT_LEFT) > freshold)) { forward(230); }
        if ((analogRead(PIN_LIGHT_RIGHT) > freshold)  &&  (analogRead(PIN_LIGHT_LEFT) < freshold)) { right(230); }
        if ((analogRead(PIN_LIGHT_RIGHT) < freshold)  &&  (analogRead(PIN_LIGHT_LEFT) > freshold)) { left(230); }
        if ((analogRead(PIN_LIGHT_RIGHT) < freshold)  &&  (analogRead(PIN_LIGHT_LEFT) < freshold)) { search(); }  
    }
}


void loop() {}


void forward(byte speed){
  digitalWrite(PIN_RIGHT_DIRECTION, HIGH); 
  digitalWrite(PIN_LEFT_DIRECTION, HIGH); 
  analogWrite(PIN_SPEED_RIGHT, speed); 
  analogWrite(PIN_SPEED_LEFT, speed); 
} 


void stop() { 
  analogWrite(PIN_SPEED_RIGHT, LOW); 
  analogWrite(PIN_SPEED_LEFT, LOW); 
  
  while (true) {
    digitalWrite(PIN_SOUND, HIGH);
    if ((analogRead(PIN_LIGHT_RIGHT) > 800)  ||  (analogRead(PIN_LIGHT_LEFT) > 800)) {
      digitalWrite(PIN_SOUND, LOW);
      break;
    }
    delay(300);
    digitalWrite(PIN_SOUND, LOW);
    delay(300);
  };
} 


void left(byte speed) { 
  digitalWrite(PIN_RIGHT_DIRECTION, LOW); 
  digitalWrite(PIN_LEFT_DIRECTION, HIGH); 
  analogWrite(PIN_SPEED_RIGHT, 230); 
  analogWrite(PIN_SPEED_LEFT, speed); 
} 


void right(byte speed) { 
  digitalWrite(PIN_RIGHT_DIRECTION, HIGH); 
  digitalWrite(PIN_LEFT_DIRECTION, LOW); 
  analogWrite(PIN_SPEED_RIGHT, speed); 
  analogWrite(PIN_SPEED_LEFT, 230); 
}


void back(byte speed) {
  digitalWrite(PIN_RIGHT_DIRECTION, LOW); 
  digitalWrite(PIN_LEFT_DIRECTION, LOW); 
  analogWrite(PIN_SPEED_RIGHT, speed); 
  analogWrite(PIN_SPEED_LEFT, speed); 
}


void search() {
  unsigned long time = millis(); 
  byte speed_increment = 100; 
  while ((analogRead(PIN_LIGHT_RIGHT) < 800) && (analogRead(PIN_LIGHT_LEFT) < 800)) { 
    delay(100); 
    left(150); 
    delay(100); 
    forward(speed_increment); 

    if (speed_increment > 150) { 
      speed_increment = 150; 
    } 
    speed_increment += 1; 
    if (millis() - time > 8000) {  
      stop();
      break;
    }
    delay(100); 
  } 
}

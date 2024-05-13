#include <Arduino.h>

#define PIN_SPEED_R 5
#define PIN_SPEED_L 6
#define PIN_DIR_R 4
#define PIN_DIR_L 7

#define PIN_SENSOR_R 1
#define PIN_SENSOR_L 0

#define PIN_BUZZER 8


#define NOTE_B0  31

#define NOTE_C1  33

#define NOTE_CS1 35

#define NOTE_D1  37

#define NOTE_DS1 39

#define NOTE_E1  41

#define NOTE_F1  44

#define NOTE_FS1 46

#define NOTE_G1  49

#define NOTE_GS1 52

#define NOTE_A1  55

#define NOTE_AS1 58

#define NOTE_B1  62

#define NOTE_C2  65

#define NOTE_CS2 69

#define NOTE_D2  73

#define NOTE_DS2 78

#define NOTE_E2  82

#define NOTE_F2  87

#define NOTE_FS2 93

#define NOTE_G2  98

#define NOTE_GS2 104

#define NOTE_A2  110

#define NOTE_AS2 117

#define NOTE_B2  123

#define NOTE_C3  131

#define NOTE_CS3 139

#define NOTE_D3  147

#define NOTE_DS3 156

#define NOTE_E3  165

#define NOTE_F3  175

#define NOTE_FS3 185

#define NOTE_G3  196

#define NOTE_GS3 208

#define NOTE_A3  220

#define NOTE_AS3 233

#define NOTE_B3  247

#define NOTE_C4  262

#define NOTE_CS4 277

#define NOTE_D4  294

#define NOTE_DS4 311

#define NOTE_E4  330

#define NOTE_F4  349

#define NOTE_FS4 370

#define NOTE_G4  392

#define NOTE_GS4 415

#define NOTE_A4  440

#define NOTE_AS4 466

#define NOTE_B4  494

#define NOTE_C5  523

#define NOTE_CS5 554

#define NOTE_D5  587

#define NOTE_DS5 622

#define NOTE_E5  659

#define NOTE_F5  698

#define NOTE_FS5 740

#define NOTE_G5  784

#define NOTE_GS5 831

#define NOTE_A5  880

#define NOTE_AS5 932

#define NOTE_B5  988

#define NOTE_C6  1047

#define NOTE_CS6 1109

#define NOTE_D6  1175

#define NOTE_DS6 1245

#define NOTE_E6  1319

#define NOTE_F6  1397

#define NOTE_FS6 1480

#define NOTE_G6  1568

#define NOTE_GS6 1661

#define NOTE_A6  1760

#define NOTE_AS6 1865

#define NOTE_B6  1976

#define NOTE_C7  2093

#define NOTE_CS7 2217

#define NOTE_D7  2349

#define NOTE_DS7 2489

#define NOTE_E7  2637

#define NOTE_F7  2794

#define NOTE_FS7 2960

#define NOTE_G7  3136

#define NOTE_GS7 3322

#define NOTE_A7  3520

#define NOTE_AS7 3729

#define NOTE_B7  3951

#define NOTE_C8  4186

#define NOTE_CS8 4435

#define NOTE_D8  4699

#define NOTE_DS8 4978

const byte SPEED_DEFAULT = 200;

const int SENSOR_THRESHOLD = 800; 

const int TIME_DELAY = 100;  
const int TIME_LIMIT = 15*1000; 

const long int CICRCLE_TIME = 14*1000;
const char notes[] = {
    60, 70, 80, 70, 80
};

void play_song()
{
}

void setup() {
  pinMode(PIN_SENSOR_R, INPUT);
  pinMode(PIN_SENSOR_L, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void stop(){
  analogWrite(PIN_SPEED_R, 0);
  analogWrite(PIN_SPEED_L, 0);
}

void move_forward(byte speed) {
  digitalWrite(PIN_DIR_R, 1);
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_R, speed);
  analogWrite(PIN_SPEED_L, speed);
}

void move_backward(byte speed) {
  digitalWrite(PIN_DIR_R, 0);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_R, speed);
  analogWrite(PIN_SPEED_L, speed);
}

void turn_left(byte speed) {
  digitalWrite(PIN_DIR_R, 0);
  digitalWrite(PIN_DIR_L, 1);
  analogWrite(PIN_SPEED_R, 255);
  analogWrite(PIN_SPEED_L, speed);
}

void turn_right(byte speed) {
  digitalWrite(PIN_DIR_R, 1);
  digitalWrite(PIN_DIR_L, 0);
  analogWrite(PIN_SPEED_R, 255);
  analogWrite(PIN_SPEED_L, speed);
}

void search() {
    byte speedSearching = 100;
    unsigned long time = millis();
    unsigned long SEARCH_DELAY = 200;

    while ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) {
      if (millis() - time > TIME_LIMIT) {
        analogWrite(PIN_SPEED_R, 0);
        analogWrite(PIN_SPEED_L, 0);
        time = millis();
        digitalWrite(PIN_BUZZER, 1);
        delay(2000);
        digitalWrite(PIN_BUZZER, 0);

        exit(1);
      }
            
      delay(SEARCH_DELAY);
      turn_left(speedSearching);

      delay(SEARCH_DELAY);
      move_forward(speedSearching);

      delay(SEARCH_DELAY);
    }
}


void loop() {
    if ((analogRead(PIN_SENSOR_R) > SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) > SENSOR_THRESHOLD)) 
      move_forward(SPEED_DEFAULT);

    if ((analogRead(PIN_SENSOR_R) > SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) 
      turn_right(SPEED_DEFAULT);
      
    if ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) > SENSOR_THRESHOLD)) 
      turn_left(SPEED_DEFAULT);

    if ((analogRead(PIN_SENSOR_R) < SENSOR_THRESHOLD) && (analogRead(PIN_SENSOR_L) < SENSOR_THRESHOLD)) 
      search();
}

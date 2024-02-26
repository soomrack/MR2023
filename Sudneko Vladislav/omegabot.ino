/*
* CONFIGURATION
* Before flashing the microcontroller firmware, make sure that the pins match
*/

#define PIN_SPEED_RIGHT               5
#define PIN_SPEED_LEFT                6
#define PIN_RIGHT_DIRECTION           4
#define PIN_LEFT_DIRECTION            7 
#define PIN_LIGHT_RIGHT               1
#define PIN_LIGHT_LEFT                0
#define PIN_SOUND                     8

/*
***************************************
* Changing the ADC frequency to speed up analogRead Part 1
* The ADC frequency is calculated by dividing the 16 MHz 
* board frequency by a divisor, the default being 128. 
* The code below sets the divisor to 16
* PS_128 - default 
* PS_16 - custom
* ADPS[2:0] devisors
* 000	2
* 001	2
* 010	4
* 011	8
* 100	16
* 101	32
* 110	64
* 111	128
***************************************
*/
const byte PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // default 111 in ADPS[2:0] with division coefficient 128 => 125 KHz
const byte PS_16 = (1 << ADPS2); // Set division coefficient to 16 => 1 MHz
// ************************************


void setup() {
    /*
    ***************************************
    * Changing the ADC frequency to speed up analogRead Part 2
    ***************************************
    */
    ADCSRA &= ~PS_128; // reset the scale 128
    ADCSRA |= PS_16; // Set scale 16 (1 MHz)
    // ************************************

    pinMode(PIN_LIGHT_RIGHT, INPUT); // Turning the right light sensor pins into environmental perception mode
    pinMode(PIN_LIGHT_LEFT, INPUT); // Turning the left light sensor pins into environmental perception mode
    pinMode(PIN_SOUND, OUTPUT);
    int freshold = 800; // Black color is more than 800, white is about 300, 
                        // for greater confidence we will set the threshold to 800
                        // the value is within [0;1023]
    while (true) { // We use a loop in the setup to disable console checking
        // If both sensors see black, drive forward
        if ((analogRead(PIN_LIGHT_RIGHT) > freshold)  &&  (analogRead(PIN_LIGHT_LEFT) > freshold)) { forward(255); }
        // If the left sensor sees white, turn right
        if ((analogRead(PIN_LIGHT_RIGHT) > freshold)  &&  (analogRead(PIN_LIGHT_LEFT) < freshold)) { right(255); }
        // If the right sensor sees white, turn left
        if ((analogRead(PIN_LIGHT_RIGHT) < freshold)  &&  (analogRead(PIN_LIGHT_LEFT) > freshold)) { left(255); }
        // If both sensors are white, the search begins
        if ((analogRead(PIN_LIGHT_RIGHT) < freshold)  &&  (analogRead(PIN_LIGHT_LEFT) < freshold)) { search(); }  
    }
}


// We can't remove the loop because then the program won't compile
void loop() {}


/*
* Function for moving forward
* @param speed The speed of the motors
*/ 
void forward(byte speed){
  digitalWrite(PIN_RIGHT_DIRECTION, HIGH); // Set the direction of right motors to forward
  digitalWrite(PIN_LEFT_DIRECTION, HIGH); // Set the direction of left motors to forward
  analogWrite(PIN_SPEED_RIGHT, speed); // Set the speed of right motors [0:255]
  analogWrite(PIN_SPEED_LEFT, speed); // Set the speed of left motors [0:255]
} 


/* 
*Function for stopping the motors 
* @param speed The speed of the motors
*/ 
void stop() { 
  analogWrite(PIN_SPEED_RIGHT, LOW); // stop the right motors
  analogWrite(PIN_SPEED_LEFT, LOW); // stop the left motors
  
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


/* 
*Function for turning left 
* @param speed The speed of the motors
*/ 
void left(byte speed) { 
  digitalWrite(PIN_RIGHT_DIRECTION, LOW); // Set the direction of right motors to backward
  digitalWrite(PIN_LEFT_DIRECTION, HIGH); // Set the direction of left motors to forward
  analogWrite(PIN_SPEED_RIGHT, 255); // Set the speed of right motors [0:255]
  analogWrite(PIN_SPEED_LEFT, speed); // Set the speed of left motors [0:255]
} 


/* 
* Function for turning right
* @param speed The speed of the motors
*/ 
void right(byte speed) { 
  digitalWrite(PIN_RIGHT_DIRECTION, HIGH); // Set the direction of right motors to forward
  digitalWrite(PIN_LEFT_DIRECTION, LOW); // Set the direction of left motors to backward
  analogWrite(PIN_SPEED_RIGHT, speed); // Set the speed of right motors [0:255]
  analogWrite(PIN_SPEED_LEFT, 255); // Set the speed of left motors [0:255]
}


/*
* Function for moving backward
* @param speed The speed of the motors
*/ 
void back(byte speed) {
  digitalWrite(PIN_RIGHT_DIRECTION, LOW); // Set the direction of right motors to backward
  digitalWrite(PIN_LEFT_DIRECTION, LOW); // Set the direction of left motors to backward
  analogWrite(PIN_SPEED_RIGHT, speed); // Set the speed of right motors [0:255]
  analogWrite(PIN_SPEED_LEFT, speed); // Set the speed of left motors [0:255]
}


/* 
* Function for searching the path
*/ 
void search() {
  // Start going in a spiral
  unsigned long time = millis(); // time from start
  byte speed_increment = 100; // Set the initial forward speed when searching
  while ((analogRead(PIN_LIGHT_RIGHT) < 800) && (analogRead(PIN_LIGHT_LEFT) < 800)) { // while both sensors are on white
    delay(100); // this is the second part of the driving time forward
    left(150); // make a left turn at a speed of 150
    delay(100); // time to turn
    forward(speed_increment); // moving forward at a higher speed = further

    // We set a speed limit, otherwise the sensors won't be able to detect the line in time.
    if (speed_increment > 150) { 
      speed_increment = 150; 
    } 
    speed_increment += 1; // increase speed = increase radius of circle
    if (millis() - time > 7000) { // if robot doesn't see line for 7 sec 
      stop();
      break;
    }
    delay(100); // this is the first part of the driving time forward
  } 
}

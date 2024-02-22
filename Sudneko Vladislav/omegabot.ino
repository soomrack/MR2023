/*
* CONFIGURATION
* Before flashing the microcontroller firmware, make sure that the pins match
*/

#define SPEED_R         5
#define SPEED_L         6
#define DIR_R           4
#define DIR_L           7 
#define LIGHT_RIGHT     1
#define LIGHT_LEFT      0

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

void Setup() {
    /*
    ***************************************
    * Changing the ADC frequency to speed up analogRead Part 2
    ***************************************
    */
    ADCSRA &= ~PS_128; // reset the scale 128
    ADCSRA |= PS_16; // Set scale 16 (1 MHz)
    // ************************************

    pinMode(LIGHT_RIGHT, INPUT); // Turning the right light sensor pins into environmental perception mode
    pinMode(LIGHT_LEFT, INPUT); // Turning the left light sensor pins into environmental perception mode
    int freshold = 800; // Black color is more than 800, white is about 300, 
                        // for greater confidence we will set the threshold to 800
    while (true) { // We use a loop in the setup to disable console checking
        // If both sensors see black, drive forward
        if ((analogRead(LIGHT_RIGHT) > freshold)  &&  (analogRead(LIGHT_LEFT) > freshold)) {forward(255);}
        // If the left sensor sees white, turn right
        if ((analogRead(LIGHT_RIGHT) > freshold)  &&  (analogRead(LIGHT_LEFT) < freshold)) {right(255);}
        // If the right sensor sees white, turn left
        if ((analogRead(LIGHT_RIGHT) < freshold)  &&  (analogRead(LIGHT_LEFT) > freshold)) {left(255);}
        // If both sensors are white, the search begins
        if ((analogRead(LIGHT_RIGHT) < freshold)  &&  (analogRead(LIGHT_LEFT) < freshold)) {search();}  
    }
}

// We can't remove the loop because then the program won't compile
void loop() {}

/*
* Function for moving forward
* @param speed The speed of the motors
*/ 
void forward(byte speed){
  digitalWrite(DIR_R, 1); // Set the direction of right motors to forward
  digitalWrite(DIR_L, 1); // Set the direction of left motors to forward
  analogWrite(SPEED_R, speed); // Set the speed of right motors to maximum
  analogWrite(SPEED_L, speed); // Set the speed of left motors to maximum
} 

/* 
*Function for stopping the motors 
* @param speed The speed of the motors
*/ 
void stop() { 
  analogWrite(SPEED_R, 0); // stop the right motors
  analogWrite(SPEED_L, 0); // stop the left motors
} 

/* 
*Function for turning left 
* @param speed The speed of the motors
*/ 
void left(byte speed) { 
  digitalWrite(DIR_R, 0); // Set the direction of right motors to backward
  digitalWrite(DIR_L, 1); // Set the direction of left motors to forward
  analogWrite(SPEED_R, 255); // Set the speed of right motors to maximum
  analogWrite(SPEED_L, speed); // Set the speed of left motors
} 

/* 
* Function for turning right
* @param speed The speed of the motors
*/ 
void right(byte speed) { 
  digitalWrite(DIR_R, 1); // Set the direction of right motors to forward
  digitalWrite(DIR_L, 0); // Set the direction of left motors to backward
  analogWrite(SPEED_R, speed); // Set the speed of right motors
  analogWrite(SPEED_L, 255); // Set the speed of left motors to maximum
} 

/*
* Function for moving backward
* @param speed The speed of the motors
*/ 
void back(byte speed) {
  digitalWrite(DIR_R, 0); // Set the direction of right motors to backward
  digitalWrite(DIR_L, 0); // Set the direction of left motors to backward
  analogWrite(SPEED_R, speed); // Set the speed of right motors to maximum
  analogWrite(SPEED_L, speed); // Set the speed of left motors to maximum
}

/* 
* Function for searching the path
*/ 
void search() {
  // At first we just assume that we went a little ahead of the road
  back(255); // we reconfigure the engines for driving backwards
  delay(300); // Let's go back
  // If this doesn't work, we start going in a spiral
  byte speedIncrement = 100; // Set the initial forward speed when searching
  while ((analogRead(LIGHT_RIGHT) < 800) && (analogRead(LIGHT_LEFT) < 800)) { // while both sensors are on white
    delay(100); // this is the second part of the driving time forward
    left(150); // make a left turn at a speed of 150
    delay(100); // time to turn
    forward(speedIncrement); // moving forward at a higher speed = further

    // We set a speed limit, otherwise the sensors won't be able to detect the line in time.
    if (speedIncrement > 150) { 
      speedIncrement = 150; 
    } 
    speedIncrement += 1; // increase speed = increase radius of circle
    delay(100); // this is the first part of the driving time forward
  } 
}
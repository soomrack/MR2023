#define SENSOR_LIGHT_PIN A0
#define SENSOR_SOIL_PIN A1
#define SENSOR_DHT_PIN 2

#define HEAT_PIN 4
#define WATER_PUMP_PIN 5
#define LED_PIN 6
#define FAN_PIN 7

#include <iarduino_DHT.h>
iarduino_DHT dht (SENSOR_DHT_PIN);

unsigned long DELAY = 2000;
int MIN_LIGHT;
float MIN_T;
float MAX_T;
int MIN_HUMIDITY;
const int DRY = 0;
const int WET = 1023;
const unsigned long int WATERING_TIME = 10000; 
const unsigned long int DELAY_TIME = 80000;

void setup() {
  Serial.begin(9600);
  
  pinMode(SENSOR_LIGHT_PIN, INPUT);
  pinMode(SENSOR_SOIL_PIN, INPUT);
  pinMode(SENSOR_DHT_PIN, INPUT);

  pinMode(HEAT_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  MIN_LIGHT = 400;
  MIN_T = 20.0;
  MAX_T = 30.0;
  MIN_HUMIDITY = 50;

}

void loop() {
  AIR_function(DELAY, MIN_T, MAX_T);
  LIGHT_function(DELAY);
  SOIL_function(DELAY, MIN_HUMIDITY, DRY, WET, WATERING_TIME, DELAY_TIME);
}

void AIR_function(unsigned long delay, float min_temp, float max_temp){
  dht.read();
  float temp;
  float hum_air;
  unsigned long int read_time_d = 0;

  temp = dht.temC();
  hum_air = dht.hum();
  
  digitalWrite(HEAT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW); 

  if(temp <= min_temp){
    Serial.println("Temperature is too low. Need to turn on fan and heater.\n");
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(HEAT_PIN, HIGH);        
  }
  else {
  if(temp >= max_temp){
    Serial.println("Temperature is too high. Need to turn on fan.\n");
    digitalWrite(FAN_PIN, HIGH);
  }
  else {
    Serial.println("Temperature is normal.\n");
  }
  }

  if (millis() - read_time_dht > delay){
    read_time_dht = millis();
    Serial.println("Waiting");
  }
}

void LIGHT_function(unsigned long delay){
  unsigned long int read_time_light = 0;
  bool light = 0;
  light = digitalRead(SENSOR_LIGHT_PIN);

  if (light == 0) {
    Serial.println("It is bright\n");
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Serial.println("It is dark. Need to turn on the light\n");
    digitalWrite(LED_PIN, HIGH);
  }

  if (millis() - read_time_light > delay){
    read_time_light = millis();
    Serial.println("Waiting");
  }
}

void SOIL_function(unsigned long delay, int MIN_HUMIDITY, int DRY, int WET, unsigned long int watering_time,  unsigned long int delay_time){
  unsigned long int read_time_soil = millis();
  unsigned int hum_soil = 0;
  hum_soil = digitalRead(SENSOR_SOIL_PIN);
  unsigned int countled;
  countled = map(hum_soil, WET, DRY, 0, 100);
  // индикация уровня влажности
  if (hum_soil <= MIN_HUMIDITY){
    digitalWrite(WATER_PUMP_PIN, HIGH);
    if (millis() - read_time_soil > watering_time){
        read_time_soil = millis();
        Serial.println("Watering in progress");
     }
    digitalWrite(WATER_PUMP_PIN, LOW);
    read_time_soil = millis();
    if (millis() - read_time_soil > delay_time){
        read_time_soil = millis();
        Serial.println("Waiting for the water to spread");
     }
  }
}

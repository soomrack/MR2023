#include <OneWire.h>

#define humidity_sensor_pin A0
#define light_sensor_pin A1
#define temperature_pin 8

#define light_pin 7
#define pompa_pin 4
#define fan_pin 5

#define border_temperature 28
#define border_light 20
#define border_humidity 30
#define delay_humidity 30

int start_hours = 0;

OneWire ds(temperature_pin);

unsigned long minutes_from_start()
{
  return (unsigned long)millis() / 60000;
}

int time_hour()
{
  return (int)(start_hours + minutes_from_start() / 60) % 24;
}

void print_info(float temperature, int light, int humidity)
{
  Serial.print("temp = ");
  Serial.print(temperature);

  Serial.print("; light = ");
  Serial.print(light);

  Serial.print("; humidity = ");
  Serial.print(humidity);
  Serial.println();
}

int humidity_sens() {
  int humidity = analogRead(humidity_sensor_pin);
  humidity = map(humidity, 0, 1023, 100, 0);
  return humidity;
}

int light_sens() {
  int light = analogRead(light_sensor_pin);
  light = map(light, 0, 1023, 0, 100);
  return light;
}

float temperature_sens() {
  byte data[2];

  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);
  delay(1000);
  ds.reset();
  ds.write(0xCC);
  ds.write(0xBE);

  data[0] = ds.read();
  data[1] = ds.read();

  return (((data[1] << 8) | data[0]) * 0.0625);
}


void start_time()
{
  int time_enter = 0;
  Serial.print("hours:");
  while(time_enter == 0)
  {
    if (Serial.available()) {
      start_hours = Serial.parseInt();
      Serial.println(start_hours);
      time_enter = 1;
    }
  }
}


void setup() {
  pinMode(humidity_sensor_pin, INPUT_PULLUP);
  pinMode(pompa_pin, OUTPUT);
  pinMode(light_sensor_pin, INPUT);

  pinMode(light_pin, OUTPUT);
  pinMode(pompa_pin, OUTPUT);
  pinMode(fan_pin, OUTPUT);

  digitalWrite(light_pin, 0);
  digitalWrite(pompa_pin, 1);
  digitalWrite(fan_pin, 1);

  Serial.begin(9600);
  Serial.setTimeout(50);
  start_time();
}

void loop() {

  int humidity, light, hours;
  unsigned long time_humidity = 0;
  float temperature;

  temperature = temperature_sens();
  light = light_sens();
  humidity = humidity_sens();

  hours = time_hour();
  Serial.println(hours);
  print_info(temperature, light, humidity);

  if (temperature > border_temperature || (hours > 17 && hours < 18))
    digitalWrite(fan_pin, 0);
  else 
    digitalWrite(fan_pin, 1);

  if (humidity < border_humidity && minutes_from_start() - time_humidity > delay_humidity)
  {
    digitalWrite(pompa_pin, 0);
    delay(2000);  
    digitalWrite(pompa_pin, 1);
    time_humidity = minutes_from_start();
  }
  else 
    digitalWrite(pompa_pin, 1);

  if (light < border_light && hours > 12 && hours < 24)
    digitalWrite(light_pin, 1);
  else
    digitalWrite(light_pin, 0);
}

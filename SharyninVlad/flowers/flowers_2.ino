#include <OneWire.h>

#define gnd_humidity_sensor_pin A0
#define air_humidity_sensor_pin A5
#define light_sensor_pin A1
#define temperature_pin 8

#define light_pin 7
#define pompa_pin 4
#define fan_pin 5

#define ON 1
#define OFF 0

struct Climate {
  int border_day_temperature = 28;
  int border_night_temperature = 20;
  int border_light = 20;
  int border_gnd_humidity = 30;
  int border_air_humidity = 30;
  int delay_gnd_humidity = 30;
}climate; 


struct Sensors {
  int start_hours;
  int hours;
  int minutes;

  int time_of_water_hour;
  int time_of_water_minute;

  float temperature;
  int light;
  int gnd_humidity;
  int air_humidity;
}sensors; 


struct State {  
  int light;
  int pump;
  int fan;
}state; 


OneWire ds(temperature_pin);

void time_update()
{
  unsigned long sec_from_start = millis() / 1000;
  sensors.minutes = (int)(sec_from_start / 60 % 60);
  sensors.hours = (int)((sensors.start_hours + sec_from_start / 3600) % 24);
}


void start_time()
{
  int time_enter = 0;
  Serial.print("hours:");
  while(!time_enter)
  {
    if (Serial.available()) {
      sensors.start_hours = Serial.parseInt();
      Serial.println(sensors.start_hours);
      time_enter = 1;
    }
  }
}


int delay_minutes(int prev_hours, int prev_minutes)
{
  return ((sensors.hours * 60 + sensors.minutes) - (prev_hours * 60 +  prev_minutes));
}


void print_info()
{
  Serial.print("temp=");
  Serial.print(sensors.temperature);

  Serial.print("; light=");
  Serial.print(sensors.light);

  Serial.print("; gnd_hum=");
  Serial.print(sensors.gnd_humidity);

  Serial.print("; air_hum=");
  Serial.print(sensors.air_humidity);

  Serial.print("; hours=");
  Serial.print(sensors.hours);

  Serial.print("; minutes=");
  Serial.print(sensors.minutes);
  Serial.println();
}

int gnd_humidity_sens() {
  int gnd_humidity = analogRead(gnd_humidity_sensor_pin);
  gnd_humidity = map(gnd_humidity, 0, 1023, 100, 0);
  return gnd_humidity;
}


int air_humidity_sens() {
  int air_humidity = analogRead(air_humidity_sensor_pin);
  air_humidity = map(air_humidity, 0, 1023, 100, 0);
  return air_humidity;
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


void sensor_update()
{  
  sensors.temperature = temperature_sens();
  sensors.light = light_sens();
  sensors.gnd_humidity = gnd_humidity_sens();
  sensors.air_humidity = air_humidity_sens();
}


void do_fan()
{
  if (sensors.hours < 8 && sensors.temperature > climate.border_night_temperature)
    state.fan |= ON;
  if (sensors.hours >= 8 && sensors.temperature > climate.border_day_temperature)
    state.fan |= ON;
  if (sensors.hours == 14)
    state.fan |= ON;
  if (sensors.hours == 20)
    state.fan |= ON;
  if (sensors.air_humidity > climate.border_air_humidity)
    state.fan |= ON;

  if (state.fan == ON)
    digitalWrite(fan_pin, 0);
  else 
    digitalWrite(fan_pin, 1);
}


void do_pump()
{
  if (sensors.gnd_humidity < climate.border_gnd_humidity)
    state.pump |= ON;

  if (delay_minutes(sensors.time_of_water_hour, sensors.time_of_water_minute) > climate.delay_gnd_humidity)
    state.pump &= ON;

  if (state.pump == ON)
  {
    digitalWrite(pompa_pin, 0);
    delay(2000);  
    digitalWrite(pompa_pin, 1);
    sensors.time_of_water_hour = sensors.hours;
    sensors.time_of_water_minute = sensors.minutes;
  }
  else 
    digitalWrite(pompa_pin, 1);
}


void do_light()
{
  if (sensors.light < climate.border_light)
    state.light |= ON;
  if (sensors.hours > 12 && sensors.hours < 24)
    state.light &= ON;

  if (state.light)
    digitalWrite(light_pin, 1);
  else
    digitalWrite(light_pin, 0);
}


void state_zero()
{
  state.fan = OFF;
  state.pump = OFF;
  state.light = OFF;
}


void setup() {
  pinMode(gnd_humidity_sensor_pin, INPUT_PULLUP);
  pinMode(air_humidity_sensor_pin, INPUT_PULLUP);
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
  state_zero();
  time_update();
  sensor_update();
  print_info();

  do_fan();
  do_pump();
  do_light();
}

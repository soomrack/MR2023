#define PIN_LIGHT_SENSOR A0
#define PIN_HUMIDITY_SENSOR A1

#define PIN_DHT_SENSOR 2
#define PIN_HEAT 4
#define PIN_WATER_PUMP 5
#define PIN_LIGHT 6
#define PIN_FAN 7

#define ON 1
#define OFF 0


#include <TroykaDHT.h>
DHT dht_sensor(PIN_DHT_SENSOR, DHT21);


int PROGRAMM_CHECK_TIME = 1;
int TIME_SET = 0;


struct Climate {
  int def_luminosity;
  int def_soil_hum;
  double min_air_temp; 
  double max_air_temp; 
  double min_air_hum; 
  double max_air_hum;
  int time_venting;
  int time_watering;
}; 


struct Sensors {
  int hours;
  int minutes;
  int seconds;

  int luminosity;
  double air_temp;
  double air_hum;
  double soil_hum;
}; 


struct State {
  long long int time_venting;
  long long int time_watering;
  long long int last_watering;
  bool regular_venting;
  bool light;
  bool fan;
  bool pump;
  bool heat;
}; 


Climate cl;
Sensors se;
State state;


void setup()
{
  Serial.begin(9600);
  dht_sensor.begin();
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_WATER_PUMP, OUTPUT);
  pinMode(PIN_DHT_SENSOR, INPUT);
  pinMode(PIN_HEAT, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);

  Serial.println("Set current time in only hours format, for example 16:34 will be 16: ");
  Serial.write(TIME_SET);
}


void plant()
{
  cl.def_luminosity = 700;
  cl.min_air_temp = 15;
  cl.max_air_temp = 30;
  cl.def_soil_hum = 90;
  cl.min_air_hum = 99;
  cl.max_air_hum = 100;
  cl.time_watering = 5000;
  cl.time_venting = 60000;
}


void custom_clock()
{
  se.seconds = millis() / 100;

  if (se.seconds == 60) {
    se.minutes += 1;
    se.seconds = 0;
  }

  if (se.minutes == 60) {
    se.hours += 1;
    se.minutes = 0;
  }

  se.hours = TIME_SET;
  
  if (se.hours == 24) {
    se.hours = 0;
  } 
}


double soil_hum_convert(int value)
{
  double persents;
  persents = (double)((1023 - value) * 100 / 1023);
  return persents;
}


void get_sensors()
{
  dht_sensor.read();

  se.soil_hum = soil_hum_convert(analogRead(PIN_HUMIDITY_SENSOR));
  se.luminosity = analogRead(PIN_LIGHT_SENSOR);
  se.air_temp = dht_sensor.getTemperatureC();
  se.air_hum = dht_sensor.getHumidity();
}


void regular_ventilation()  
{
  state.time_venting += PROGRAMM_CHECK_TIME * 1000;

  if (se.minutes % 4 == 0) { 
    state.regular_venting = ON;
    state.time_venting = 0;
  } else {
    if (state.time_venting > cl.time_venting) {
      state.regular_venting = OFF;
    } else {
      state.regular_venting = ON;
    }
  }
}


void air_temp()
{
  if (se.air_temp < cl.min_air_temp) {
    state.fan = ON;
    state.heat = ON;
  }

  else if (se.air_temp > cl.max_air_temp) {
    state.fan = ON;
    state.heat = OFF;
  }
  
  else {
    state.fan = OFF;
    state.heat = OFF;
  }
}


void air_hum()
{
  if (se.air_hum < cl.min_air_hum) {
    state.fan = OFF;
    state.pump = ON;
  }

  else if (se.air_hum > cl.max_air_hum) {
    state.fan = ON;
    state.pump = OFF;
  }
  
  else {
    state.fan = OFF;
    state.pump = OFF;
  }
}


void soil_hum()
{
  if (se.soil_hum < cl.def_soil_hum) {
    state.pump = ON;
  } else {
    state.pump = OFF;
  }
}


void light()
{
  if (se.luminosity >= cl.def_luminosity) {
    state.light = ON;
  } else {
    state.light = OFF;
  }
}


void day_cycle()
{
  if (se.hours < 6 || se.hours > 22){
    state.regular_venting = OFF;
    state.light = OFF;
  }
}


void do_light()
{
  digitalWrite(PIN_LIGHT, state.light);
}


void do_heat()
{
  if (state.heat == ON) {
    digitalWrite(PIN_FAN, ON);
    digitalWrite(PIN_HEAT, ON);
  } else {
    digitalWrite(PIN_HEAT, OFF);
  }
}


void do_vent()
{
  if (state.regular_venting == ON){
    digitalWrite(PIN_FAN, ON);
  } else if (state.fan == ON) {
    digitalWrite(PIN_FAN, ON);
  } else {
    digitalWrite(PIN_FAN, OFF);
  }
}


void do_pump()
{ 
  if (state.last_watering > 60000) {
    if (state.pump == ON) {
      digitalWrite(PIN_WATER_PUMP, state.pump);
      state.time_watering += PROGRAMM_CHECK_TIME * 1000;

      if (state.time_watering > cl.time_watering) {
        digitalWrite(PIN_WATER_PUMP, OFF);
        state.time_watering = 0;
        state.last_watering = 0;
      } 
    } else {
      digitalWrite(PIN_WATER_PUMP, state.pump);
    }
  }

  state.last_watering += PROGRAMM_CHECK_TIME * 1000;
}


void periodic_check()
{
  get_sensors();

  light();
  air_temp();
  air_hum();
  regular_ventilation();
  soil_hum();
  
  //day_cycle();

  do_light();
  do_heat();
  do_vent();
  do_pump();
}


void loop()
{
  plant();
  custom_clock();

  if (se.seconds % PROGRAMM_CHECK_TIME == 0) { 
    delay(800);
    periodic_check();
  }
  /* 
  digitalWrite(PIN_LIGHT, HIGH);
  digitalWrite(PIN_FAN, HIGH);
  digitalWrite(PIN_HEAT, HIGH);
  digitalWrite(PIN_WATER_PUMP, HIGH);
  delay(1000); */
}

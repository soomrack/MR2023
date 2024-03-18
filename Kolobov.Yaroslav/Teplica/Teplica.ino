#include <TroykaDHT.h> 
 
#define LIGHT_SENSOR A0 //Датчик освещенности 
#define LED_STRIP 6 //Светодиодная лента 
#define SOIL_MOISTURE_SENSOR A1 //Датчик влажности почвы 
#define WATER_PUMP 5 //водяная помпа 
#define AIR_DHT_SENSOR 2 //датчик влажности и температуры воздуха 
#define FAN_HEATING 4 //нагревательный элемент вентилятора 
#define FAN 7 //вентилятор 
 
DHT dht_sensor(AIR_DHT_SENSOR, DHT21); 
int DAY = 1; 

struct Conditions
{
 int normal_luminocity;
 int normal_soil_humidity;
 double min_air_temperature;
 double max_air_temperature;
 double min_air_humidity;
 double max_air_humidity;  
};

 
struct Indications
{
  int luminocity;
  double air_temp;
  double air_humidity;
  int soil_humidity;
}

struct State
{
  bool pump;
  bool light;
  bool fan;
  bool heat;
  bool ventilation;
}

State state;
Indications indications;
Conditions conditions;


void luminocity()
{
  if (indications.luminocity < conditions.normal_luminocity) {
    state.light = 1;
  } else {
    state.light = 0;
  }
}


void air_temp()
{
  if (indications.air_temp <= conditions.max_air_temperature && indications.air_temp >= conditions.min_air_temperature) {
    state.fan = 0; // fan off
    state.heat = 0; // heat off
  } else if (indications.air_temp >= conditions.max_air_temperature) {
    state.fan = 1; // fan on
    state.heat = 0; // heat off
  } else {
    state.fan = 1; // fan on
    state.heat = 1; // heat on
  }
}


void air_humidity()
{
  if (Indications.air_humidity < Conditions.min_air_humidity) {
    state.pump = 1; // pump on
  } else if(Indications.air_humidity > Conditions.min_air_humidity){
    state.fan = 1; 
  }
}


void soil_humidity()
{
  if (Indications.soil_humidity < Conditions.normal_soil_humidity) {
    state.pump = 1;
  }
}


void ventilation(const int seconds)
{
  if (seconds % 600 == 0) {
    while(millis() / 1000 - seconds >= 30) {
    state.ventilation = 1;
    fan();
    }
    state.ventilation = 0;
    fan();
  } 
}

void fan()
{
  if (state.fan == 1 || state.ventilation == 1) {
    digitalWrite(FAN, HIGH);
  } else {
    digitalWrite(FAN, LOW);
  }
} 


void pump(const int seconds)
{
  if (state.pump == 1) {
    while (millis() / 1000 - seconds <= 4) {
      digitalWrite(WATER_PUMP, HIGH);
    }
  }
  digitalWrite(WATER_PUMP, LOW)
  state.pump = 0;
} 


void heat()
{
  if (state.heat == 1) {
    digitalWrite(FAN_HEATING, HIGH);
  } else {
    digitalWrite(FAN_HEATING, LOW);
  }
}


void light()
{
  if (state.light == 1) {
    digitalWrite(LED_STRIP, HIGH);
  }
}

void sensors_read()
{
  indications.luminocity = analogRead(LIGHT_SENSOR);
  indications.soil_humidity = analogRead(SOIL_MOISTURE_SENSOR);
  indications.air_humidity = dht_sensor.getHumidity();
  indications.air_temp = dht_sensor.getTemperatureC();
}


void night_check(const int seconds)
{
  if (seconds / DAY >= (16 * 60 * 60)) {
    while(millis() / 1000 - seconds < 8 * 60 * 60)
    {
      all_off();
    }
    DAY++;
  }
}


void all_off()
{
  state.fan = 0;
  state.heat = 0;
  state.light = 0;
  state.pump = 0;
  state.ventilation = 0;
}

void cycle()
{
  int seconds = millis() / 1000;

 
  if (seconds % 10 == 0) {
    
    all_off();

    sensors_read();

    luminocity();
    air_humidity();
    air_temp();
    soil_humidity();

    night_check(seconds);

    fan();
    light();
    pump();
    heat();
  }
  
  void ventilation(seconds);
}


void setup() { 
  Serial.begin(9600); 
  pinMode(LED_STRIP, OUTPUT); 
 
} 


void loop() { 

}
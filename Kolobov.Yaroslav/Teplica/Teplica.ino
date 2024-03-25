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
 int watering_time;
int watering_interval; // minutes
};

 
struct Sensors // лучше написать Sensors или Data OK
{
  int luminocity;
  double air_temp;
  double air_humidity;
  int soil_humidity;
};

struct State
{
  bool fan_ventilation;
  bool fan_temperature;
  bool fan_humidity_air;
  bool fan_humidity_soil;
  bool pump_humidity_air;
  bool pump_humidity_soil;
  bool light;
  bool heat;
  bool day;
};

struct Time
{
  int days;
  long int hours;
  int minutes;
  int seconds;
};

State state;
Sensors sensors;
Conditions conditions ;
Time time;

void plant_carrot()  // состояние среды подходящее для морковки
{
 conditions.normal_luminocity = 400;
 conditions.normal_soil_humidity = 500;
 conditions.min_air_temperature = 20;
 conditions.max_air_temperature = 30;
 conditions.min_air_humidity = 10;
 conditions.max_air_humidity = 60 ;
 conditions.watering_time = 3;
 conditions.watering_interval = 2;
}


void set_plant()  // устанавливает тип растения
{
  int plant_type = 1;

  switch(plant_type){
    case 1: plant_carrot(); break;

    default: Serial.println("недопустимы тип");
  }
}


void init()
{ 
pinMode(LED_STRIP, OUTPUT); //Светодиодная лента 
pinMode(WATER_PUMP, OUTPUT); //водяная помпа 
pinMode(AIR_DHT_SENSOR, INPUT); //датчик влажности и температуры воздуха 
pinMode(FAN_HEATING, OUTPUT); //нагревательный элемент вентилятора 
pinMode(FAN, OUTPUT); //вентилятор 
}

void time_counter()
{
  time.days = millis() / (1000 * 60 * 60 * 24);
  time.hours = millis() / (1000 * 60 * 60) - time.days * 24;
  time.minutes = millis() / (1000 * 60) - time.hours * 60;
  time.seconds = millis() / 1000 - time.minutes * 60;
}

void day() 
{ 
  if ((time.hours < 8) || (time.hours > 16)) { 
    state.day = 0; 
  } else { 
    state.day = 1; 
  } 
}

void luminocity()
{
  if (sensors.luminocity < conditions.normal_luminocity && state.day == 1) {
    state.light = 1;
  } else {
    state.light = 0;
  }
}


void air_temp()
{
  if (sensors.air_temp <= conditions.max_air_temperature && sensors.air_temp >= conditions.min_air_temperature) {
    state.fan_temperature = 0; // fan off
    state.heat = 0; // heat off
  } else if (sensors.air_temp >= conditions.max_air_temperature) {
    state.fan_temperature = 1; // fan on
    state.heat = 0; // heat off
  } else {
    state.fan_temperature = 1; // fan on
    state.heat = 1; // heat on
  }
}


void air_humidity()
{
  if (sensors.air_humidity < conditions.min_air_humidity) {
    state.pump_humidity_air = 1; // pump on
  } else if(sensors.air_humidity > conditions.min_air_humidity){
    state.fan_humidity_air = 1; 
  } else {
    state.fan_humidity_air = 0;
    state.pump_humidity_air = 0;
  }
}


void soil_humidity()
{
  if (sensors.soil_humidity < conditions.normal_soil_humidity) {
    state.pump_humidity_soil = 1;
  } else if (sensors.soil_humidity > conditions.normal_soil_humidity){
    state.fan_humidity_soil = 1;
  } else {
    state.fan_humidity_soil = 0;
    state.pump_humidity_soil = 0;
  }
}


void ventilation()
{
  if (time.hours % 4 == 0 && time.minutes < 2) {
    state.fan_ventilation = 1;
  } else {
    state.fan_ventilation = 0;
  }
}

void do_fan()
{
  if (state.fan_ventilation == 1 || state.fan_temperature == 1 || 
      state.fan_humidity_air == 1 || state.fan_humidity_soil == 1) {
        digitalWrite(FAN, HIGH);
        return;
  }
    digitalWrite(FAN, LOW);
} 


void do_pump()
{
  static int previous_watering;

  if ((state.pump_humidity_air == 1 || state.pump_humidity_soil == 1 && (time.minutes - previous_watering >= conditions.watering_interval))) {
    long long int watering_start = millis();
    while ((millis() / 1000) - watering_start / 1000 < conditions.watering_time) {
      digitalWrite(WATER_PUMP, HIGH);
      previous_watering = time.minutes;
    }
  }
  digitalWrite(WATER_PUMP, LOW);
} 


void do_heat()
{
  if (state.heat == 1) {
    digitalWrite(FAN_HEATING, HIGH);
  } else {
    digitalWrite(FAN_HEATING, LOW);
  }
}


void do_light()
{
  if (state.light == 1) {
    digitalWrite(LED_STRIP, HIGH);
  } else {
    digitalWrite(LED_STRIP, LOW);
  }
}

void sensors_read()
{
  sensors.luminocity = analogRead(LIGHT_SENSOR);
  sensors.soil_humidity = analogRead(SOIL_MOISTURE_SENSOR);
  sensors.air_humidity = dht_sensor.getHumidity();
  sensors.air_temp = dht_sensor.getTemperatureC();
}






// state.fan_ventilation
// state.fan_temperature
// state.fan_humidity
// do_fan формат для актуаторов
// функция, которая возвращает состояние ночь или не ночь
// функция time должна возвращать реальное время, на случай если принесут часы 

void cycle()
{
  time_counter();

  if (time.seconds % 10 == 0) {
    sensors_read();
    day(); 


    luminocity();
    air_humidity();
    air_temp();
    soil_humidity();
    ventilation();


    do_fan();
    do_light();
    do_pump();
    do_heat();
  }
}


void setup() { 
  Serial.begin(9600);
  init(); 
} 


void loop() { 
  cycle();
}
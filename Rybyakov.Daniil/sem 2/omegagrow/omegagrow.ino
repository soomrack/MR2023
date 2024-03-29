#define PIN_LIGHT_SENSOR A0  // датчик освещенности
#define PIN_LIGHT 6  // светодиодная лента
#define PIN_HUMIDITY_SENSOR A1  // датчик влажности почвы 0 - влажно 1023 - сухо
#define PIN_WATER_PUMP 5  // водяной насос
#define PIN_DHT_SENSOR 2  // датчик температуры и влажности воздуха
#define PIN_VEN_HEAT 4  // нагреватель вентилтора 
#define PIN_VEN 7  // вентилятор
#define ON 1  // включение цифровых выходов
#define OFF 0  // выключение цифровых выходов

#include <TroykaDHT.h>
DHT dht_sensor(PIN_DHT_SENSOR, DHT21);

int PROGRAMM_CHECK_TIME = 1; // период проверки программы в секундах

struct Climate  {
  int norm_luminosity;
  double min_air_temp; 
  double max_air_temp; 
  double min_air_humidity; 
  double max_air_humidity; 
  int norm_ground_humidity;
  int watering_time;
  int ven_time;
}; 


struct Sensors  {
  int hours;
  int minutes;
  int seconds;
  int luminosity;  // 0 - светло / 1023 - темно
  double air_temp;  // градусы
  double air_humidity;  // проценты
  int ground_humidity;  // 0 - влажно / 1023 - сухо
}; 


struct State  {
  long long int ven_time;
  long long int watering_time;
  long long int last_watering;
  bool regular_ven;
  bool light;
  bool ven;
  bool pump;
  bool heat;
}; 

State state;
Climate clim;
Sensors sens;


void setup()  // включает нужные пины в необходимые режимы работы
{
  Serial.begin(9600);
  dht_sensor.begin();
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_WATER_PUMP, OUTPUT);
  pinMode(PIN_DHT_SENSOR, INPUT);
  pinMode(PIN_VEN_HEAT, OUTPUT);
  pinMode(PIN_VEN, OUTPUT);
}


void plant_strawberry()  // состояние среды подходящее для клубники
{
  clim.norm_luminosity = 400;
  clim.min_air_temp = 20;
  clim.max_air_temp = 30;
  clim.norm_ground_humidity = 500;
  clim.min_air_humidity = 10;
  clim.max_air_humidity = 60;
  clim.watering_time = 5000;
  clim.ven_time = 2 * 60 * 1000;
}


void plant_cucumber() // состояние среды подходящее для огурцов
{
  clim.norm_luminosity = 200;
  clim.min_air_temp = 10;
  clim.max_air_temp = 25;
  clim.norm_ground_humidity = 100;
  clim.min_air_humidity = 15;
  clim.max_air_humidity = 50;
  clim.watering_time = 5000;
  clim.ven_time = 2 * 60 * 1000;
}


void plant_carrot()  // состояние среды подходящее для морковки
{
  clim.norm_luminosity = 250;
  clim.min_air_temp = 15;
  clim.max_air_temp = 20;
  clim.norm_ground_humidity = 500;
  clim.min_air_humidity = 20;
  clim.max_air_humidity = 55;
  clim.watering_time = 5000;
  clim.ven_time = 2 * 60 * 1000;
}


void set_plant()  // устанавливает тип растения
{
  int plant_type = 1;

  switch(plant_type){
    case 1: plant_strawberry(); break;
    case 2: plant_cucumber(); break;
    case 3: plant_carrot(); break;
    default: Serial.println("недопустимы тип");
  }
}


void set_time()  // снятие данных с часов
{
  sens.seconds = millis() / 1000;

  if (sens.seconds == 60){
    sens.minutes += 1;
    sens.seconds = 0;
  }
  if (sens.minutes == 60){
    sens.hours += 1;
    sens.minutes = 0;
  }
  if (sens.hours == 24){
    sens.hours = 0;
  } 
}


void get_sensors()  // снятие данных с датчиком
{
  dht_sensor.read();

  sens.ground_humidity = analogRead(PIN_HUMIDITY_SENSOR);
  sens.luminosity = analogRead(PIN_LIGHT_SENSOR);
  sens.air_temp = dht_sensor.getTemperatureC();
  sens.air_humidity = dht_sensor.getHumidity();
}


void ventilation()  
{
  state.ven_time += PROGRAMM_CHECK_TIME * 1000;
  if (sens.minutes % 10 == 0){ 
    state.regular_ven = ON;
    state.ven_time = 0;
  }
  else {
    if (state.ven_time > clim.ven_time){
      state.regular_ven = OFF;
    }
    else{
      state.regular_ven = ON;
    }
  }
}


void air_temp()
{
  if (sens.air_temp >= clim.min_air_temp && sens.air_temp <= clim.max_air_temp){
    state.ven = OFF;
    state.heat = OFF;
  } 
  if (sens.air_temp < clim.min_air_temp){
    state.ven = ON;
    state.heat = ON;
  }
  if (sens.air_temp > clim.max_air_temp){
    state.ven = ON;
    state.heat = OFF;
  }
}


void air_humidity()
{
  if (sens.air_humidity >= clim.min_air_humidity && sens.air_humidity <= clim.max_air_humidity){
    state.ven = OFF;
    state.pump = OFF;
  } 
  if (sens.air_humidity < clim.min_air_humidity){
    state.ven = OFF;
    state.pump = ON;
  }
  if (sens.air_humidity > clim.max_air_humidity){
    state.ven = ON;
    state.pump = OFF;
  }
}


void ground_humidity()
{
  if (sens.ground_humidity >= clim.norm_ground_humidity){
    state.pump = ON;
  }
  else{
    state.pump = OFF;
  }
}


void light()
{
  if (sens.luminosity >= clim.norm_luminosity){
    state.light = ON;
  }
  else{
    state.light = OFF;
  }
}


void day_night()
{
  if (sens.hours < 6 || sens.hours > 22){
    state.regular_ven = OFF;
    state.light = OFF;
  }
}


void do_light()
{
  digitalWrite(PIN_LIGHT, state.light);
}


void do_heat()
{
  if (state.heat == ON){
    digitalWrite(PIN_VEN, ON);
    digitalWrite(PIN_VEN_HEAT, ON);
  }
  else{
    digitalWrite(PIN_VEN_HEAT, OFF);
  }
}


void do_vent()
{
  if (state.regular_ven == ON){
    digitalWrite(PIN_VEN, ON);
  }
  else if (state.ven == ON){
    digitalWrite(PIN_VEN, ON);
  }
  else{
    digitalWrite(PIN_VEN, OFF);
  }
}


void do_pump()
{ 
  if (state.last_watering > (300000)){  // секунды
    if (state.pump == ON){
      digitalWrite(PIN_WATER_PUMP, state.pump);
      state.watering_time += PROGRAMM_CHECK_TIME * 1000;
      if (state.watering_time > clim.watering_time){
        digitalWrite(PIN_WATER_PUMP, OFF);
        state.watering_time = 0;
        state.last_watering = 0;
      } 
    }
    else{
      digitalWrite(PIN_WATER_PUMP, state.pump);
    }
  }
  state.last_watering += PROGRAMM_CHECK_TIME * 1000;
}


void periodic_check()  // функция вызывающая проверку состояния системы
{
  get_sensors();

  air_temp();
  air_humidity();
  ventilation();
  ground_humidity();
  light();

  //day_night();

  do_light();
  do_vent();
  do_heat();  // нагревание после вентиляции!!!!!!!!!!!!!!!!!!!!!!
  do_pump();
}


void loop()  // главная функция
{
  set_plant(); 
  set_time();
  if (sens.seconds % PROGRAMM_CHECK_TIME == 0){ delay(800); periodic_check();}
}
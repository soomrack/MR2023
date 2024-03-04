#define PIN_LIGHT_SENSOR A0 // датчик освещенности
#define PIN_LIGHT 6 // светодиодная лента
#define PIN_HUMIDITY_SENSOR A1 // датчик влажности почвы 0 - влажно 1023 - сухо
#define PIN_WATER_PUMP 5 // водяной насос
#define PIN_DHT_SENSOR 2 // датчик температуры и влажности воздуха
#define PIN_VEN_HEAT 4 // нагреватель вентилтора 
#define PIN_VEN 7 // вентилятор

#include <TroykaDHT.h>

DHT dht_sensor(PIN_DHT_SENSOR, DHT21);

//минимальные и максимальные значения освещенности, температуры и влажности почвы 
//буду отличаться в зависимости от типа растения
int MIN_PIN_LIGHT;
int MAX_PIN_LIGHT;
double MIN_TEMP;
double MAX_TEMP;
double MIN_AIR_HUMIDITY;
double MAX_AIR_HUMIDITY;
int MIN_HUMIDITY;


void setup() // включает нужные пины в необходимые режимы работы
{
  Serial.begin(9600);
  dht_sensor.begin();
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_WATER_PUMP, OUTPUT);
  pinMode(PIN_DHT_SENSOR, INPUT);
  pinMode(PIN_VEN_HEAT, OUTPUT);
  pinMode(PIN_VEN, OUTPUT);
}

void set_plant() // устанавливает тип растения
{
  int plant_type;
  // 1-клубника , 2-огруцы , 3-морковь
  plant_type = 1;
  switch(plant_type){
    case 1:
      MIN_PIN_LIGHT = 400;
      MAX_PIN_LIGHT = 800;
      MIN_TEMP = 20;
      MAX_TEMP = 30;
      MIN_HUMIDITY = 50;
      MIN_AIR_HUMIDITY = 10;
      MAX_AIR_HUMIDITY = 60;
      break;
    case 2:
      MIN_PIN_LIGHT = 200;
      MAX_PIN_LIGHT = 600;
      MIN_TEMP = 10;
      MAX_TEMP = 25;
      MIN_HUMIDITY = 100;
      MIN_AIR_HUMIDITY = 15;
      MAX_AIR_HUMIDITY = 50;
      break;
    case 3: 
      MIN_PIN_LIGHT = 250;
      MAX_PIN_LIGHT = 500;
      MIN_TEMP = 15;
      MAX_TEMP = 20;
      MIN_HUMIDITY = 500;
      MIN_AIR_HUMIDITY = 20;
      MAX_AIR_HUMIDITY = 55;
      break;
    default:
      Serial.println("недопустимы тип");
  }
}

void check_light() // проверяет освещенность в теплице
{
  if (analogRead(PIN_LIGHT_SENSOR) < MIN_PIN_LIGHT){digitalWrite(PIN_LIGHT, HIGH);}
  if (analogRead(PIN_LIGHT_SENSOR) > MAX_PIN_LIGHT){digitalWrite(PIN_LIGHT, LOW);}
}

void check_DHT() // проверяет влажность и температуру воздуха
{
  dht_sensor.read();
  float air_temp;
  float air_humidity;
  switch(dht_sensor.getState()) {
    case DHT_OK:
      air_temp = dht_sensor.getTemperatureC();
      air_humidity = dht_sensor.getHumidity();

      if (air_temp > MAX_TEMP) {digitalWrite(PIN_VEN, HIGH), digitalWrite(PIN_VEN_HEAT, LOW);}
      else if(air_temp < MAX_TEMP && air_temp > MIN_TEMP) {digitalWrite(PIN_VEN, LOW), digitalWrite(PIN_VEN_HEAT, LOW);}
      else {digitalWrite(PIN_VEN_HEAT, HIGH), digitalWrite(PIN_VEN, HIGH);}

      if (air_humidity > MAX_HUMIDITY) {digitalWrite(PIN_VEN, HIGH);}
      else if(air_humidity < MAX_HUMIDITY && air_humidity > MIN_HUMIDITY) {digitalWrite(PIN_VEN, LOW);}
      else {digitalWrite(PIN_WATER_PUMP, HIGH), digitalWrite(PIN_VEN, LOW), delay(2000), digitalWrite(PIN_WATER_PUMP, LOW);}

    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;

    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;

    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;

  }
}

void check_humidity() // проверяет влажность почвы
{
  if (analogRead(PIN_HUMIDITY_SENSOR) < MIN_HUMIDITY){
    digitalWrite(PIN_WATER_PUMP, HIGH); 
    delay(10000);
    digitalWrite(PIN_WATER_PUMP, LOW);
  }
}

void night ()
{
  digitalWrite(PIN_LIGHT, LOW);

}

timer()
{
  // long hours = millis()/(1000*60*60);
  // if (hours > 24){hours = 0;}
  // long days = millis()/(1000*60*60*24);

  int minutes = 0;
  int hours = 0;
  int days = 0;

  if (hours < 6 || hours > 20){
    digitalWrite(PIN_LIGHT, LOW);
    check_DHT();
  }
  else {
    if (hours % 2 = 0){digitalWrite(PIN_VEN, HIGH), delay(600000), digitalWrite(PIN_VEN, LOW);}
    check_light();
    check_humidity();
    check_DHT();
  }

}

void loop() // главная функция
{
  set_plant();
  timer();
}
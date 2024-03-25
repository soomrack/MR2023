#define SENSOR_LED_PIN A0
#define LED_PIN 6
#define SENSOR_HUMIDITRY_PIN A1
#define WATER_PUMP_PIN 5
#define SENSOR_DHT_PIN 2
#define HEAT_PIN 4
#define FAN_PIN 7
#include <TroykaDHT.h>
DHT dht_sensor(SENSOR_DHT_PIN, DHT21);

unsigned long DELAY = 2000;
int MIN_LIGHT;
float MIN_T;
float MAX_T;
int MIN_HUMIDITRY;
const int DRY_SOIL_HUMIDITRY = 0;
const int WET_SOIL_HUMIDITRY = 1023;
const unsigned long int WATERING_TIME = 10000;
const unsigned long int DELAY_TIME = 80000;

void setup() {
  Serial.begin(9600);
  dht_sensor.begin();
  
  pinMode(SENSOR_LED_PIN, INPUT);
  pinMode(SENSOR_HUMIDITRY_PIN, INPUT);
  pinMode(SENSOR_DHT_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(HEAT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

//дефолт настройки, можно сделать так, чтобы можно было менять
Serial.println("Теплица работает"); 
MIN_LIGHT = 400;
MIN_T = 20.0;
MAX_T = 30.0;
MIN_HUMIDITRY = 50;

void loop() {
  DHT_function(DELAY, MIN_T, MAX_T);
  LED_function(DELAY);
  HUM_function(DELAY, MIN_HUMIDITRY, DRY_SOIL_HUMIDITRY, WET_SOIL_HUMIDITRY, WATERING_TIME, DELAY_TIME);
}

void DHT_function(unsigned long delay, float min_temp, float max_temp){
  dht_sensor.read();
  float temperature;
  float humid_air;
  unsigned long int time_dht_read = 0;
  // проверяем состояние данных
  switch(dht_sensor.getState()) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      temperature = dht_sensor.getTemperatureC();
      humid_air = dht_sensor.getHumidity();
      Serial.print("Temperature = ");
      Serial.print(temperature);
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(dht_sensor.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(dht_sensor.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(humid_air);
      Serial.println(" %");
      digitalWrite(HEAT_PIN, LOW);
      digitalWrite(FAN_PIN, LOW); 
      if(temperature <= min_temp){
        Serial.println("Temperature is too low. Need to turn on fan and heater.\n");
        digitalWrite(FAN_PIN, HIGH);
        digitalWrite(HEAT_PIN, HIGH);        
      } else {
        if(temperature >= max_temp){
          Serial.println("Temperature is too high. Need to turn on fan.\n");
          digitalWrite(FAN_PIN, HIGH);
        } else {
          Serial.println("Temperature is normal.\n");
        }
      }
      if (millis() - time_dht_read > delay){
        time_dht_read = millis();
        Serial.println("Waiting");
      }
      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // данных нет, датчик не реагирует или отсутствует
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }
}

void LED_function(unsigned long delay){
  unsigned long int time_led_read = 0;
  bool led_lvl = 0;
  led_lvl = digitalRead(SENSOR_LED_PIN);

  if (led_lvl == 0) {
    Serial.println("It is bright\n");
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("It is dark. Need to turn on the light\n");
    digitalWrite(LED_PIN, HIGH);
  }
  if (millis() - time_led_read > delay){
        time_led_read = millis();
        Serial.println("Waiting");
      }
}

void HUM_function(unsigned long delay, int min_humiditry, int dry_soil_humidity, int wet_soil_humidity, unsigned long int watering_time,  unsigned long int delay_time){
  unsigned long int time_hum_read = millis();
  unsigned int hum_lvl = 0;
  hum_lvl = digitalRead(SENSOR_HUMIDITRY_PIN);
  unsigned int countled;
  countled = map(hum_lvl, wet_soil_humidity, dry_soil_humidity, 0, 100);
  // индикация уровня влажности
  if (hum_lvl <= MIN_HUMIDITRY){
    digitalWrite(WATER_PUMP_PIN, HIGH);
    if (millis() - time_hum_read > watering_time){
        time_hum_read = millis();
        Serial.println("Watering in progress");
     }
    digitalWrite(WATER_PUMP_PIN, LOW);
    time_hum_read = millis();
    if (millis() - time_hum_read > delay_time){
        time_hum_read = millis();
        Serial.println("Waiting for the water to spread");
     }
  }

}

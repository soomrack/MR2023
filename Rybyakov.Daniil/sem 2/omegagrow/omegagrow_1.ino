#define PIN_LIGHT_SENSOR A0 // датчик освещенности
#define PIN_LIGHT 6 // светодиодная лента
#define PIN_HUMIDITY_SENSOR A1 // датчик влажности почвы 0 - влажно 1023 - сухо
#define PIN_WATER_PUMP 5 // водяной насос
#define PIN_DHT_SENSOR 2 // датчик температуры и влажности воздуха
#define PIN_VEN_HEAT 4 // нагреватель вентилтора 
#define PIN_VEN 7 // вентилятор
#define ON 1 // включение цифровых выходов
#define OFF 0 // выключение цифровых выходов
#define DAY 1 // день
#define NIGHT 0 // ночь
#define FIX 1 // нуждается в принятии мер
#define OK 0 // не нуждается в принятии мер

#include <TroykaDHT.h>
DHT dht_sensor(PIN_DHT_SENSOR, DHT21);


struct Environment  
{
  int time_of_day;
  int min_luminosity; 
  double min_air_temp; 
  double max_air_temp; 
  double min_air_humidity; 
  double max_air_humidity; 
  int min_ground_humidity; 
  int watering_time = 5000; 
  int hours; 
  int minutes; 
  int ground_humidity; // FIX или OK / 1 или 0
  int luminosity; // FIX или OK / 1 или 0
  int regular_ven; // ON или OFF / 1 или 0
  int ven; // ON или OFF / 1 или 0
  int ven_heat; // ON или OFF / 1 или 0
  double air_temp; // FIX или OK / 1 или 0
  double air_humidity; // FIX или OK / 1 или 0
  int time_of_ven; // время в течении которого будет работать вентилятор
  int water_pump;
  // 0-й элемент вектора: день/ночь (TIME_OF_DAY)
};

Environment env;


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


void plant_strawberry() // состояние среды подходящее для клубники
{
  env.min_luminosity = 400;
  env.min_air_temp = 20;
  env.max_air_temp = 30;
  env.min_ground_humidity = 50;
  env.min_air_humidity = 10;
  env.max_air_humidity = 60;
}


void plant_cucumber() // состояние среды подходящее для огурцов
{
  env.min_luminosity = 200;
  env.min_air_temp = 10;
  env.max_air_temp = 25;
  env.min_ground_humidity = 100;
  env.min_air_humidity = 15;
  env.max_air_humidity = 50;
}


void plant_carrot() // состояние среды подходящее для морковки
{
  env.min_luminosity = 250;
  env.min_air_temp = 15;
  env.max_air_temp = 20;
  env.min_ground_humidity = 500;
  env.min_air_humidity = 20;
  env.max_air_humidity = 55;
}


void set_plant() // устанавливает тип растения
{
  int plant_type = 1;

  switch(plant_type){
    case 1: plant_strawberry(); break;
    case 2: plant_cucumber(); break;
    case 3: plant_carrot(); break;
    default: Serial.println("недопустимы тип");
  }
}


void set_time() // снятие данных с часов
{
  env.hours = 0;
  env.minutes = 0;
}


void check_day_time() // проверяет сейчас день или ночь
{
  if (env.hours > 6 && env.hours < 20){ // ночь будет с 20.00 до 6.00
    env.time_of_day = DAY; 
  }
  else {
    env.time_of_day = NIGHT; 
  }
}


void check_regular_ven() // проверяет насстало ли время регулярного проветривания
{
  if (env.time_of_day == DAY && (env.hours % 1 == 0) && (env.minutes % 10 == 0)){ // регулярное проветривание будет проходить раз в час
    env.regular_ven = ON; 
  }
  else {
    env.regular_ven = OFF;
  }
}


void check_air_temp() // проверяет температуру воздуха
{
  if (env.air_temp < env.max_air_temp && env.air_temp > env.min_air_temp){ 
    env.air_temp = OK; 
  }
  else{
    env.air_temp = FIX; 
  }
}


void check_air_humidity() // проверяет влажность воздуха
{
  if (env.air_humidity < env.max_air_humidity && env.air_humidity > env.min_air_humidity){
    env.air_humidity = OK;
  }
  else{
    env.air_humidity = FIX; 
  }
}


void do_light(int status) // по надобности включает свет
{
  digitalWrite(PIN_LIGHT, status);
}


void do_ven(int status) // по надобности включает вентилятор
{
  digitalWrite(PIN_VEN, status);
}


void do_ven_heat(int status) // по надобности включает обогреватель
{
  digitalWrite(PIN_VEN_HEAT, status);
}


void do_watering(int status) // по надобности включает полив на какое-то время
{
  digitalWrite(PIN_WATER_PUMP, status);
  delay(env.watering_time);
}


void time_day() // алгоритм действи если сейчас день
{
  if (env.luminosity < env.min_luminosity){ // проверка на достаточную освещенность
    env.luminosity = ON; 
  }
  else{
    env.luminosity = OFF; 
  }

  if (env.ground_humidity < env.min_ground_humidity){ // проверка на влажность почвы
    env.ground_humidity = ON; 
  }
  else{
    env.ground_humidity = OFF; 
  }

  if (env.regular_ven == ON){ // проверка на работу регулярного проветривания
    env.ven = ON; 
    if (env.air_temp < env.min_air_temp){ // проверка на превышение минимальной температуру
        env.ven_heat = ON; 
      }
    else{
      env.ven_heat = OFF; 
    }
  }
  else{ //регулярное проветривание не работает
    if (env.air_humidity > env.max_air_humidity){ // проврека на превышени влажности воздуха
      env.ven = ON; 
      if (env.air_temp < env.min_air_temp){ // проверка на превышение минимальной температуру
        env.ven_heat = ON; 
      }
      else{
        env.ven_heat = OFF; 
      }
    }
    else if (env.air_humidity < env.max_air_humidity && env.air_humidity > env.min_air_humidity){ // влажность воздуха в рамках допустимой
      if (env.air_temp > env.max_air_temp){ // проверка температуры воздууха
        env.ven = ON; 
        env.ven_heat = ON;
      }
      else{
        env.ven = OFF; 
        env.ven_heat = OFF;
      }
    }
    else{ // влажность воздуха ниже допустимой
      if (env.ground_humidity == ON){ // проверяем поливали ли уже почву
        env.air_humidity = OFF; 
      }
      else{
      env.air_humidity = ON; 
      }
      }
    }
    if (env.air_humidity == ON || env.ground_humidity == ON){ // требуется полив либо для почвы либо для воздуха
      env.water_pump = ON; 
    }
    else{
      env.water_pump = OFF; 
    }
}


void time_night() // алгоритм действи если сейчас
{
  env.luminosity = OFF; 
  env.regular_ven = OFF; 

  if (env.ground_humidity < env.min_ground_humidity){ // проверка на влажность почвы
    env.ground_humidity = ON; 
  }
  else{
    env.ground_humidity = OFF;
  }

  if (env.air_humidity > env.max_air_humidity){ // проврека на превышени влажности воздуха
    env.ven = ON; 
    if (env.air_temp < env.min_air_temp){ // проверка на превышение минимальной температуру
        env.ven_heat = ON; 
    else{
        env.ven_heat = OFF; 
    }
    }
  else if (env.air_humidity < env.max_air_humidity && env.air_humidity > env.min_air_humidity){ // влажность воздуха в рамках допустимой
    if (env.air_temp > env.max_air_temp){ // проверка температуры воздууха
      env.ven = ON; 
      env.ven_heat = ON;
    }
    else{
      env.ven = OFF; 
      env.ven_heat = OFF;
    }
  }
  else{ // влажность воздуха ниже допустимой
    if (env.ground_humidity == ON){ // проверяем поливали ли уже почву
      env.air_humidity = OFF; 
    }
    else{
    env.air_humidity = ON; 
    }
    }
    if (env.air_humidity == ON || env.ground_humidity == ON){ // требуется полив либо для почвы либо для воздуха
      env.water_pump = ON; 
    }
    else{
      env.water_pump = OFF; 
    }
}


void check_status() // получение значений с датчиков
{
  dht_sensor.read();
  env.ground_humidity = analogRead(PIN_HUMIDITY_SENSOR);
  env.luminosity = analogRead(PIN_LIGHT_SENSOR);
  env.air_temp = dht_sensor.getTemperatureC();
  env.air_humidity = dht_sensor.getHumidity();
}


void setting_values() // проверка условий
{
  check_day_time(); 
  check_regular_ven(); 
  check_air_temp(); 
  check_air_humidity(); 

  if (env.time_of_day == DAY){time_day();} 
  else {time_night();} 
}


void realization() // включение необходимых элеметов
{
  do_light(env.luminosity);
  do_ven(env.ven);
  do_ven_heat(env.ven_heat);
  do_watering(env.water_pump);
}


void periodic_check() // каждые две минуты запускает программу
{
  if (env.minutes % 2 == 0){
    check_status();
    setting_values();
    realization();
  }
}


void loop() // главная функция
{
  set_time();
  periodic_check();
}
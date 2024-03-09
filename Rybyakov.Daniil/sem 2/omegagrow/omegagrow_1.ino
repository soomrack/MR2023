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

//значения будут отличаться в зависимости от типа растения
int MIN_LUMINOSITY; // минимальная освещенность
double MIN_AIR_TEMP; // минимальная температура воздуха
double MAX_AIR_TEMP; // максимальная температура воздуха
double MIN_AIR_HUMIDITY; // минимальная влажность воздуха
double MAX_AIR_HUMIDITY; // максимальная влажность воздуха
int MIN_GROUND_HUMIDITY; // минимальная влажность почвы
int WATERING_TIME = 5000; // время поливки 5 секунд

// глобальные переменные в которых хранится состояние 
int HOURS; // время в часах получаемое с часов
int MINUTES; // время в минутах получаемое с часов
int GROUND_HUMIDITY; // FIX или OK / 1 или 0
int LUMINOSITY; // FIX или OK / 1 или 0
int REGULAR_VEN; // ON или OFF / 1 или 0
int VEN; // ON или OFF / 1 или 0
int VEN_HEAT; // ON или OFF / 1 или 0
double AIR_TEMP; // FIX или OK / 1 или 0
double AIR_HUMIDITY; // FIX или OK / 1 или 0
int TIME_OF_VEN; // время в течении которого будет работать вентилятор
int VECTOR_STATUS[9]; // вектор состояний в котором будет хранится нынешнее состояние системы для дальнейшего воздействия
// 0-й элемент вектора: день/ночь (TIME_OF_DAY)
// 1-й элемент вектора: освещенность (LUMINOSITY)
// 2-й элемент вектора: влажность почвы (GROUND_HUMIDITY)
// 3-й элемент вектора: температура (AIR_TEMP)
// 4-й элемент вектора: влажность воздуха (AIR_HUMIDITY)
// 5-й элемент вектора: регулярне проветривание (REGULAR_VEN)
// 6-й элемент вектора: работа вентилятора (зависит от влажности воздуха и температуры) (VEN)
// 7-й элемент вектора: работа нагревательного элемена (зависит от температуры и работы вентилятора) (VEN_HEAT)
// 8-й элемент вектора: работа водяного насоса


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
  MIN_LUMINOSITY = 400;
  MIN_AIR_TEMP = 20;
  MAX_AIR_TEMP = 30;
  MIN_GROUND_HUMIDITY = 50;
  MIN_AIR_HUMIDITY = 10;
  MAX_AIR_HUMIDITY = 60;
}


void plant_cucumber() // состояние среды подходящее для огурцов
{
  MIN_LUMINOSITY = 200;
  MIN_AIR_TEMP = 10;
  MAX_AIR_TEMP = 25;
  MIN_GROUND_HUMIDITY = 100;
  MIN_AIR_HUMIDITY = 15;
  MAX_AIR_HUMIDITY = 50;
}


void plant_carrot() // состояние среды подходящее для морковки
{
  MIN_LUMINOSITY = 250;
  MIN_AIR_TEMP = 15;
  MAX_AIR_TEMP = 20;
  MIN_GROUND_HUMIDITY = 500;
  MIN_AIR_HUMIDITY = 20;
  MAX_AIR_HUMIDITY = 55;
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
  HOURS = 0;
  MINUTES = 0;
}


void check_day_time() // проверяет сейчас день или ночь
{
  if (HOURS > 6 && HOURS < 20){ // ночь будет с 20.00 до 6.00
    VECTOR_STATUS[0] = DAY; //сейчас день
  }
  else {
    VECTOR_STATUS[0] = NIGHT; // сейчас ночь
  }
}


void check_regular_ven() // проверяет насстало ли время регулярного проветривания
{
  if (VECTOR_STATUS[0] == DAY && (HOURS % 1 == 0) && (MINUTES % 10 == 0)){ // регулярное проветривание будет проходить раз в час
    VECTOR_STATUS[5] = ON; // когда наступает время включает проветривание
  }
  else {
    VECTOR_STATUS[5] = OFF; // когда наступает время выключает проветривание
  }
}


void check_air_temp() // проверяет температуру воздуха
{
  if (AIR_TEMP < MAX_AIR_TEMP && AIR_TEMP > MIN_AIR_TEMP){ 
    VECTOR_STATUS[3] = OK; // температура в рамках нормы
  }
  else{
    VECTOR_STATUS[3] = FIX; // требуется нагрев или охлаждение
  }
}


void check_air_humidity() // проверяет влажность воздуха
{
  if (AIR_HUMIDITY < MAX_AIR_HUMIDITY && AIR_HUMIDITY > MIN_AIR_HUMIDITY){
    VECTOR_STATUS[4] = OK; // влажность в рамках нормы
  }
  else{
    VECTOR_STATUS[4] = FIX; // требуется увлажнение или проветривание
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
  delay(WATERING_TIME);
}


void time_day() // алгоритм действи если сейчас день
{
  if (LUMINOSITY < MIN_LUMINOSITY){ // проверка на достаточную освещенность
    VECTOR_STATUS[1] = ON; // включаем если света недостаточно
  }
  else{
    VECTOR_STATUS[1] = OFF; // выключаем если света достаточно
  }

  if (GROUND_HUMIDITY < MIN_GROUND_HUMIDITY){ // проверка на влажность почвы
    VECTOR_STATUS[2] = ON; // полив нужен
  }
  else{
    VECTOR_STATUS[2] = OFF; // полив не нужен
  }

  if (VECTOR_STATUS[5] == ON){ // проверка на работу регулярного проветривания
    VECTOR_STATUS[6] = ON; // если регулярное проветривание работает вентилятор работает
    if (AIR_TEMP < MIN_AIR_TEMP){ // проверка на превышение минимальной температуру
        VECTOR_STATUS[7] = ON; // из-за холода включаем нагреватель
      }
    else{
      VECTOR_STATUS[7] = OFF; // нагреватель выключаем для охлаждения
    }
  }
  else{ //регулярное проветривание не работает
    if (AIR_HUMIDITY > MAX_AIR_HUMIDITY){ // проврека на превышени влажности воздуха
      VECTOR_STATUS[6] = ON; // из-за повышенной влажности включаем вентилятор
      if (AIR_TEMP < MIN_AIR_TEMP){ // проверка на превышение минимальной температуру
        VECTOR_STATUS[7] = ON; // из-за холода включаем нагреватель
      }
      else{
        VECTOR_STATUS[7] = OFF; // нагреватель выключаем для охлаждения
      }
    }
    else if (AIR_HUMIDITY < MAX_AIR_HUMIDITY && AIR_HUMIDITY > MIN_AIR_HUMIDITY){ // влажность воздуха в рамках допустимой
      if (AIR_TEMP > MAX_AIR_TEMP){ // проверка температуры воздууха
        VECTOR_STATUS[6] = ON; // включаем и вентилятор и нагреватель
        VECTOR_STATUS[7] = ON;
      }
      else{
        VECTOR_STATUS[6] = OFF; // выключаем и вентилятор и нагреватель
        VECTOR_STATUS[7] = OFF;
      }
    }
    else{ // влажность воздуха ниже допустимой
      if (VECTOR_STATUS[2] == ON){ // проверяем поливали ли уже почву
        VECTOR_STATUS[4] = OFF; // почву уже поливали (полив не нужен)
      }
      else{
      VECTOR_STATUS[4] = ON; // нужно полить для увелечения влажности воздуха
      }
      }
    }
    if (VECTOR_STATUS[4] == ON || VECTOR_STATUS[2] == ON){ // требуется полив либо для почвы либо для воздуха
      VECTOR_STATUS[8] = ON; // будет активировать насос
    }
    else{
      VECTOR_STATUS[8] = OFF; // почву поливатть не надо
    }
}


void time_night() // алгоритм действи если сейчас
{
  VECTOR_STATUS[1] = OFF; // ночью не нужен свет
  VECTOR_STATUS[5] = OFF; // ночью не нужно регулярное проветривание

  if (GROUND_HUMIDITY < MIN_GROUND_HUMIDITY){ // проверка на влажность почвы
    VECTOR_STATUS[2] = ON; // полив нужен
  }
  else{
    VECTOR_STATUS[2] = OFF; // полив не нужен
  }

  if (AIR_HUMIDITY > MAX_AIR_HUMIDITY){ // проврека на превышени влажности воздуха
    VECTOR_STATUS[6] = ON; // из-за повышенной влажности включаем вентилятор
    if (AIR_TEMP < MIN_AIR_TEMP){ // проверка на превышение минимальной температуру
        VECTOR_STATUS[7] = ON; // из-за холода включаем нагреватель
    }
    else{
        VECTOR_STATUS[7] = OFF; // нагреватель выключаем для охлаждения
    }
    }
  else if (AIR_HUMIDITY < MAX_AIR_HUMIDITY && AIR_HUMIDITY > MIN_AIR_HUMIDITY){ // влажность воздуха в рамках допустимой
    if (AIR_TEMP > MAX_AIR_TEMP){ // проверка температуры воздууха
      VECTOR_STATUS[6] = ON; // включаем и вентилятор и нагреватель
      VECTOR_STATUS[7] = ON;
    }
    else{
      VECTOR_STATUS[6] = OFF; // выключаем и вентилятор и нагреватель
      VECTOR_STATUS[7] = OFF;
    }
  }
  else{ // влажность воздуха ниже допустимой
    if (VECTOR_STATUS[2] == ON){ // проверяем поливали ли уже почву
      VECTOR_STATUS[4] = OFF; // почву уже поливали (полив не нужен)
    }
    else{
    VECTOR_STATUS[4] = ON; // нужно полить для увелечения влажности воздуха
    }
    }
    if (VECTOR_STATUS[4] == ON || VECTOR_STATUS[2] == ON){ // требуется полив либо для почвы либо для воздуха
      VECTOR_STATUS[8] = ON; // будет активировать насос
    }
    else{
      VECTOR_STATUS[8] = OFF; // почву поливать не надо
    }
}


void check_status() // получение значений с датчиков
{
  dht_sensor.read();
  GROUND_HUMIDITY = analogRead(PIN_HUMIDITY_SENSOR);
  LUMINOSITY = analogRead(PIN_LIGHT_SENSOR);
  AIR_TEMP = dht_sensor.getTemperatureC();
  AIR_HUMIDITY = dht_sensor.getHumidity();
}


void setting_values() // проверка условий
{
  check_day_time(); // запись значений в вектор состояний
  check_regular_ven(); // запись значений в вектор состояний
  check_air_temp(); // запись значений в вектор состояний
  check_air_humidity(); // запись значений в вектор состояний

  if (VECTOR_STATUS[0] == DAY){time_day();} // запускает программу соответствующую дню
  else {time_night();} // запускает программу соответствующую ночи
}


void realization() // включение необходимых элеметов
{
  do_light(VECTOR_STATUS[1]);
  do_ven(VECTOR_STATUS[6]);
  do_ven_heat(VECTOR_STATUS[7]);
  do_watering(VECTOR_STATUS[8]);
}


void periodic_check() // кааждые две минуты запускает программу
{
  if (MINUTES % 2 == 0){
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
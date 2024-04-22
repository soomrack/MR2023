#include <TroykaDHT.h>

#define LUX_SENSOR A0  // датчик освещенности
#define LED_STRIP 6  // светодиодная лента
#define HUMIDITY_SENSOR A1  // датчик влажности почвы: 0 - влажно, 1023 - сухо
#define WATER_PUMP 5  // водяной насос
#define ATAD_SENSOR 2  // датчик температуры и влажности воздуха
#define HEAT_VENT 4  // нагреватель вентилтора 
#define VENTILATION 7  // вентилятор
#define WATER 3 //время полива


DHT dht(ATAD_SENSOR, DHT21);


struct Climate {
  int min_light;
  double min_temp;
  double max_temp;
  double min_humidity;
  double max_humidity;
  int min_soil_humidity;
  int max_soil_humidity;
  long int watering_time;
};


struct Sensors  {
  int light;
  double temperature;
  double humidity;
  int soil_humidity;
};


struct State  {
  bool ven_temp;
  bool light;
  bool ven;
  bool pump;
  bool heat;
  bool day;
  long int last_watering;
  long int watering_time;
}; 

struct Time
{
  int days;
  long int hours;
  int min;
  int sec;
};

State state;
Climate clim;
Sensors sens;
Time time;




void plant_raspberry()  // состояние среды подходящее для малины
{
  clim.min_light = 250;
  clim.min_temp = 40;
  clim.max_temp = 50;
  clim.min_soil_humidity = 20;
  clim.max_soil_humidity = 120;
  clim.min_humidity = 10;
  clim.max_humidity = 60;
  clim.watering_time = 5000;

}


void plant_cabbage()       // состояние среды подходящее для капусты
{ 
  clim.min_light = 300;
  clim.min_temp = 40;
  clim.max_temp = 45;
  clim.min_soil_humidity = 70;
  clim.max_soil_humidity = 260;
  clim.min_humidity = 15;
  clim.max_humidity = 80;
  clim.watering_time = 5000;
}


void plant_watermelon()  // состояние среды подходящее для арбуза
{
clim.min_light = 450;
  clim.min_temp = 40;
  clim.max_temp = 60;
  clim.min_soil_humidity = 140;
  clim.max_soil_humidity = 420;
  clim.min_humidity = 65;
  clim.max_humidity = 90;
  clim.watering_time = 5000;
}

void set_plant()  // устанавливает тип растения
{
  int plant_type = 1;

  switch(plant_type){
    case 1: plant_raspberry(); break;
    case 2: plant_cabbage(); break;
    case 3: plant_watermelon(); break;
    default: Serial.println("недопустимый тип");
  }
}

void set_time()  // снятие данных с часов
{
  time.hours = 0;
  time.min = 0;
}

void get_sensors()  // снятие данных с датчиком
{
  dht.read();
  sens.soil_humidity = analogRead(HUMIDITY_SENSOR);
  sens.light = analogRead(LUX_SENSOR);
  sens.temperature = dht.getTemperatureC();
  sens.humidity = dht.getHumidity();
}


void ventilation()  
{
  if ((time.days % 4 == 0) && (time.hours == 13)){
    state.ven = 1;
  }
}

void air_temp()
{
  if (sens.temperature >= clim.min_temp && sens.temperature <= clim.max_temp) {
    state.ven = 1;
    state.heat = 1;
  }

  if (sens.temperature < clim.min_temp) {
    state.ven = 0;
    state.heat = 0;
  }

  if (sens.temperature > clim.max_temp) {
    state.ven = 0;
    state.heat = 1;
  }
}


void air_humidity()
{
  if (sens.humidity >= clim.min_humidity && sens.humidity <= clim.max_humidity) {
    state.ven = 1;
    state.pump = 0;
  }

  if (sens.humidity < clim.min_humidity) {
    state.ven = 1;
    state.pump = 1;
  }

  if (sens.humidity > clim.max_humidity) {
    state.ven = 0;
    state.pump = 0;
  }
}

void ground_humidity()
{
  if (sens.soil_humidity < clim.min_humidity){
    state.pump = 0;
  }
  else{
    state.pump = 1;
  }
}


void light()
{
  if (sens.light > clim.min_light){
    state.light = 1;
  }
  else{
    state.light = 0;
  }
}

void do_light()
{
  if(state.light == 1){
    digitalWrite(LED_STRIP, 1);
  } else {
    digitalWrite(LED_STRIP, 0);
  }
}

void time_counter()
{
  time.days = millis() / (1000 * 60 * 60 * 24);
  time.hours = millis() / (1000 * 60 * 60) - time.days * 24;
  time.min = millis() / (1000 * 60) - time.hours * 60;
  time.sec = millis()/(1000*60) - time.min*60;
}


void do_heat()
{
  if (state.heat == 1){
    digitalWrite(VENTILATION, 1);
    digitalWrite(HEAT_VENT, 1);
  }
  else{
    digitalWrite(HEAT_VENT, 0);
  }
}


void do_vent()
{
  if (state.ven == 1){
    digitalWrite(VENTILATION, 1);
  }
  else{
    digitalWrite(VENTILATION, 0);
  }
}

// bool work_time(){

// }

void do_pump()
{ 
  if (state.last_watering > (100000)){  // секунды
    if (state.pump == 1){
      digitalWrite(WATER_PUMP, 1);
      state.watering_time += 1000;
      if (state.watering_time > 500000){
        digitalWrite(WATER_PUMP, 0);
        state.watering_time = 0;
        state.last_watering = 0;
      } 
    }
    else{
      digitalWrite(WATER_PUMP, 0);
    }
  }
  state.last_watering += 1000;
}


void periodic_check()  // каждые 10 секунд запускает программу
{
  time_counter();
  if (time.sec % 10 == 0){
    get_sensors();
    ventilation();
    air_temp();
    air_humidity();
    ground_humidity();
    light();

    do_light();
    do_heat(); 
    do_vent();   
    do_pump();
  }
}

void setup()  // включает нужные пины в необходимые режимы работы
{
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_STRIP, OUTPUT);
  pinMode(WATER_PUMP, OUTPUT);
  pinMode(ATAD_SENSOR, INPUT);
  pinMode(HEAT_VENT, OUTPUT);
  pinMode(VENTILATION, OUTPUT);
}

void loop() {
  set_plant();
  periodic_check();
  Serial.println(state.last_watering);
  // set_time();
}
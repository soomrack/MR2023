#define PIN_LIGHT_SENSOR A0  // light sensor
#define PIN_LIGHT 6  // LED Strip Light
#define PIN_HUMIDITY_SENSOR A1  // soil moisture sensor 0 - wet 1023 - dry
#define PIN_WATER_PUMP 5  // water pump
#define PIN_DHT_SENSOR 2  // air temperature and humidity sensor
#define PIN_FAN_HEAT 4  // fan heater
#define PIN_FAN 7  // fan

#include <TroykaDHT.h>


DHT dht_sensor(PIN_DHT_SENSOR, DHT21);


const long int PAUSE_TIME = 1000; //ms


struct ClimateType {
    int norm_luminosity;
    double min_air_temp; 
    double max_air_temp; 
    double min_air_humidity; 
    double max_air_humidity; 
    int norm_ground_humidity;
    long long int watering_time;
    long long int watering_duration;
    long long int ven_time;
    long long int ven_duration;
} Climate;


struct {
    int luminosity;       // 0 – light / 1023 – dark
    double air_temp;      // degrees
    double air_humidity;  // percentage
    int ground_humidity;  // 0 - wet / 1023 - dry
} Sensors; 


struct {
    long long int last_ven_time;
    long long int last_watering_time;
    bool light;
    bool ven;
    bool pump;
    bool heat;
} State;


const ClimateType StrawberryClimate = {
    .norm_luminosity = 400,
    .min_air_temp = 20,
    .max_air_temp = 30,
    .min_air_humidity = 10,
    .max_air_humidity = 60,
    .norm_ground_humidity = 500,
    .watering_time = 12ul * 60ul * 60ul *1000ul,
    .watering_duration = 30ul *1000ul,
    .ven_time = 2ul * 60ul * 1000ul,
    .ven_duration = 1ul * 60ul *1000ul
};


const ClimateType CucumberClimate = {
    .norm_luminosity = 200,
    .min_air_temp = 10,
    .max_air_temp = 25,
    .min_air_humidity = 15,
    .max_air_humidity = 50,
    .norm_ground_humidity = 100,
    .watering_time = 12ul * 60ul * 60ul *1000ul,
    .watering_duration = 30ul *1000ul,
    .ven_time = 2ul * 60ul * 1000ul,
    .ven_duration = 1ul * 60ul *1000ul
};


const ClimateType CarrotClimate = {
    .norm_luminosity = 250,
    .min_air_temp = 15,
    .max_air_temp = 20,
    .min_air_humidity = 20,
    .max_air_humidity = 55,
    .norm_ground_humidity = 500,
    .watering_time = 12ul * 60ul * 60ul *1000ul,
    .watering_duration = 30ul *1000ul,
    .ven_time = 2ul * 60ul * 1000ul,
    .ven_duration = 1ul * 60ul *1000ul
};


void setup() {
    Serial.begin(9600);
    dht_sensor.begin();

    pinMode(PIN_LIGHT, OUTPUT);
    pinMode(PIN_WATER_PUMP, OUTPUT);
    pinMode(PIN_DHT_SENSOR, INPUT);
    pinMode(PIN_FAN_HEAT, OUTPUT);
    pinMode(PIN_FAN, OUTPUT);

    Climate = CucumberClimate;
}


void sensors_update()  // снятие данных с датчиком
{
    Sensors.ground_humidity = analogRead(PIN_HUMIDITY_SENSOR);
    Sensors.luminosity = analogRead(PIN_LIGHT_SENSOR);

    dht_sensor.read();
    switch(dht_sensor.getState()) {
        case DHT_OK:
            Sensors.air_temp = dht_sensor.getTemperatureC();
            Sensors.air_humidity = dht_sensor.getHumidity();
        case DHT_ERROR_CHECKSUM:
            Serial.println("Checksum error");
            break;
        case DHT_ERROR_TIMEOUT:
            Serial.println("Time out error");
            break;
        case DHT_ERROR_NO_REPLY:
            Serial.println("Sensor not c1nected");
            break;
    }
}


void state_update()
{
    State.heat = Sensors.air_temp < Climate.min_air_temp;
    State.light = Sensors.luminosity < Climate.norm_luminosity;
    
    State.ven = State.heat || Sensors.air_temp > Climate.max_air_temp || Sensors.air_humidity > Climate.max_air_humidity;
    if (State.ven || (millis() - State.last_ven_time - Climate.ven_time) > Climate.ven_duration)
        State.last_ven_time = millis();
    State.ven |= (millis() - State.last_ven_time) > Climate.ven_time;

    State.pump = Sensors.air_humidity < Climate.min_air_humidity || Sensors.ground_humidity < Climate.norm_ground_humidity;
    if (State.pump || (millis() - State.last_watering_time - Climate.watering_duration) > Climate.watering_duration)
        State.last_watering_time = millis();
    State.pump |= (millis() - State.last_watering_time) > Climate.watering_time;
}


void write_state()
{
    digitalWrite(PIN_LIGHT, State.light);
    digitalWrite(PIN_FAN_HEAT, State.heat);
    digitalWrite(PIN_FAN, State.ven);
    digitalWrite(PIN_WATER_PUMP, State.pump);
}


void loop() {
    sensors_update();
    state_update();
    write_state();
    delay(PAUSE_TIME);
}

#define PIN_LIGHT_SENSOR A0
#define PIN_HUMIDITY_SENSOR A1
#define PIN_DHT_SENSOR 2

#define PIN_LED 6
#define PIN_WATER_PUMP 5
#define PIN_VENT 7
#define PIN_VENT_HEATER 4

#include <TroykaDHT.h>

DHT DHTSensor(PIN_DHT_SENSOR, DHT21);  // DHT sensor handler
int CHECKOUT_PERIOD = 1000; // milliseconds


struct Climate {
    // DHT sensor parameters
    double humidityMinimum;
    double humidityMaximum;
    double temperatureMinimum;
    double temperatureMaximum;

    // Regular sensor parameters
    int lightOptimal;
    int humidityGroundOptimal;

    // Procedures time periods
    int wateringPeriod = 300000;
    int wateringTimeout = 5 * 1000;
    int ventTimeout = 2 * 60 * 1000;
};


struct Greenhouse {
    // Greenhouse clock
    int hours;
    int minutes;
    int seconds;

    // Checkouts time
    long long int ventTime;
    long long int wateringTime;
    long long int wateringTimeLast;

    // Greenhouse states
    bool ventilating;
    bool lighting;
    bool cooling;
    bool watering;
    bool heating;

    // DHT sensor data
    double temperature;
    double humidity;

    // Regular sensors data
    int light;
    int humidityGround;
};

Climate climate;
Greenhouse greenhouse;


void setClimate(int plant = 1) {
    switch (plant) {
        case 1:
            climate.lightOptimal = 400;
            climate.temperatureMinimum = 20;
            climate.temperatureMaximum = 30;
            climate.humidityGroundOptimal = 500;
            climate.humidityMinimum = 10;
            climate.humidityMaximum = 60;
            break;

        case 2:
            climate.lightOptimal = 200;
            climate.temperatureMinimum = 10;
            climate.temperatureMaximum = 25;
            climate.humidityGroundOptimal = 100;
            climate.humidityMinimum = 15;
            climate.humidityMaximum = 50;
            break;

        case 3:
            climate.lightOptimal = 250;
            climate.temperatureMinimum = 15;
            climate.temperatureMaximum = 20;
            climate.humidityGroundOptimal = 500;
            climate.humidityMinimum = 20;
            climate.humidityMaximum = 55;
            break;

        default:
            Serial.println("Unknown plant");
            exit(-1);
    }
}


void updateClock() {
    greenhouse.seconds = millis() / 1000;

    if (greenhouse.seconds >= 60) {
        greenhouse.minutes += 1;
        greenhouse.seconds = 0;
    }

    if (greenhouse.minutes >= 60) {
        greenhouse.hours += 1;
        greenhouse.minutes = 0;
    }

    if (greenhouse.hours >= 24)
        greenhouse.hours = 0;
}


void updateData() {
    DHTSensor.read();

    greenhouse.temperature = DHTSensor.getTemperatureC();
    greenhouse.humidity = DHTSensor.getHumidity();

    greenhouse.light = analogRead(PIN_LIGHT_SENSOR);
    greenhouse.humidityGround = analogRead(PIN_HUMIDITY_SENSOR);
}


void ventCheckout() {
    greenhouse.ventTime += CHECKOUT_PERIOD;

    if (greenhouse.minutes % 10 == 0) {
        greenhouse.ventilating = true;
        greenhouse.ventTime = 0;
    } else {
        if (greenhouse.ventTime > climate.ventTimeout) greenhouse.ventilating = false;
        else greenhouse.ventilating = true;
    }
}


void temperatureCheckout() {
    if (greenhouse.temperature >= climate.temperatureMinimum && greenhouse.temperature <= climate.temperatureMaximum) {
        greenhouse.cooling = false;
        greenhouse.heating = false;
    }
    if (greenhouse.temperature < climate.temperatureMinimum) {
        greenhouse.cooling = true;
        greenhouse.heating = true;
    }
    if (greenhouse.temperature > climate.temperatureMaximum) {
        greenhouse.cooling = true;
        greenhouse.heating = false;
    }
}


void humidityCheckout() {
    if (greenhouse.humidity >= climate.humidityMinimum && greenhouse.humidity <= climate.humidityMaximum) {
        greenhouse.cooling = false;
        greenhouse.watering = false;
    }
    if (greenhouse.humidity < climate.humidityMinimum) {
        greenhouse.cooling = false;
        greenhouse.watering = true;
    }
    if (greenhouse.humidity > climate.humidityMaximum) {
        greenhouse.cooling = true;
        greenhouse.watering = false;
    }
}


void humidityGroundCheckout() {
    if (greenhouse.humidityGround >= climate.humidityGroundOptimal) greenhouse.watering = true;
    else greenhouse.watering = false;
}


void lightCheckout() {
    if (greenhouse.light >= climate.lightOptimal) greenhouse.lighting = true;
    else greenhouse.lighting = false;
}


void lightingProcedure() {
    if (greenhouse.lighting) digitalWrite(PIN_LED, 1);
    else digitalWrite(PIN_LED, 0);
}


void heatingProcedure() {
    if (greenhouse.heating) {
        digitalWrite(PIN_VENT, 1);
        digitalWrite(PIN_VENT_HEATER, 1);
    } else digitalWrite(PIN_VENT_HEATER, 0);
}


void ventilationProcedure() {
    if (greenhouse.ventilating || greenhouse.cooling) digitalWrite(PIN_VENT, 1);
    else digitalWrite(PIN_VENT, 0);
}


void wateringProcedure() {
    if (greenhouse.wateringTimeLast > climate.wateringPeriod) {
        if (greenhouse.watering) {
            digitalWrite(PIN_WATER_PUMP, 1);
            greenhouse.wateringTime += CHECKOUT_PERIOD;

            if (greenhouse.wateringTime > climate.wateringTimeout) {
                digitalWrite(PIN_WATER_PUMP, 0);
                greenhouse.wateringTime = 0;
                greenhouse.wateringTimeLast = 0;
            }
        } else digitalWrite(PIN_WATER_PUMP, 1);
    }

    greenhouse.wateringTimeLast += CHECKOUT_PERIOD;
}


void setup() {
    Serial.begin(9600);

    DHTSensor.begin();
    pinMode(PIN_DHT_SENSOR, INPUT);

    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_WATER_PUMP, OUTPUT);
    pinMode(PIN_VENT, OUTPUT);
    pinMode(PIN_VENT_HEATER, OUTPUT);

    setClimate(3); // switch with 1 for strawberry, 2 for cucumber or 3 for carrot
}


void loop() {
    updateClock();

    if (greenhouse.seconds % (CHECKOUT_PERIOD / 1000) == 0) {
        updateData();

        // Perform regular checkouts
        lightCheckout();
        temperatureCheckout();
        humidityCheckout();
        humidityGroundCheckout();
        ventCheckout();

        // Perform procedures
        lightingProcedure();
        ventilationProcedure();
        heatingProcedure();
        wateringProcedure();
    }
}
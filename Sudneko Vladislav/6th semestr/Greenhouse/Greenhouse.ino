#define LIGHT_SENSOR_PIN      A0
#define LIGHT_PIN             6
#define HUMIDITY_SENSOR_PIN   A1
#define WATER_PUMP_PIN        5
#define DHT_SENSOR_PIN        2
#define VENT_HEAT_PIN         4
#define VENT_PIN              7
#define ON_STATE              1
#define OFF_STATE             0

#include <DHT.h>
DHT dhtSensor(DHT_SENSOR_PIN, DHT21);

int CHECK_INTERVAL = 10; // seconds

struct SystemState {
  long long int ventilationTime;
  long long int wateringTime;
  long long int lastWatering;
  bool regularVentilation;
  bool lightOn;
  bool ventilationOn;
  bool pumpOn;
  bool heaterOn;
};

struct SensorValues {
  int hours;
  int minutes;
  int seconds;
  int lightIntensity;
  double airTemperature;
  double airHumidity;
  int soilHumidity;
};

struct PlantConditions {
  int lightThreshold;
  double minTemperature;
  double maxTemperature;
  double minAirHumidity;
  double maxAirHumidity;
  int soilHumidityThreshold;
  int wateringDuration;
  int ventilationDuration;
};

SystemState systemState;
PlantConditions plantConditions;
SensorValues sensorValues;


void setup() {
  Serial.begin(9600);
  dhtSensor.begin();
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(DHT_SENSOR_PIN, INPUT);
  pinMode(VENT_HEAT_PIN, OUTPUT);
  pinMode(VENT_PIN, OUTPUT);

  int plantType;
  Serial.println(
      "Enter plant type (1: Strawberry, 2: Cucumber, 3: Carrot, 4: Custom from "
      "file):");
  while (!Serial.available()) {
  }  // Wait for input
  plantType = Serial.parseInt();
  Serial.println(plantType);

  setPlantType(plantType);
}


void setPlantConditions(int lightThreshold, double minTemperature,
                        double maxTemperature, double minAirHumidity,
                        double maxAirHumidity, int soilHumidityThreshold,
                        int wateringDuration, int ventilationDuration) {
  plantConditions.lightThreshold = lightThreshold;
  plantConditions.minTemperature = minTemperature;
  plantConditions.maxTemperature = maxTemperature;
  plantConditions.minAirHumidity = minAirHumidity;
  plantConditions.maxAirHumidity = maxAirHumidity;
  plantConditions.soilHumidityThreshold = soilHumidityThreshold;
  plantConditions.wateringDuration = wateringDuration;
  plantConditions.ventilationDuration = ventilationDuration;
}




void setPlantType(int plantType) {
  switch (plantType) {
    case 1:
      setPlantConditions(400, 20, 30, 50, 80, 500, 5000, 120000);
      break;  // Strawberry
    case 2:
      setPlantConditions(200, 10, 25, 60, 90, 300, 6000, 180000);
      break;  // Cucumber
    case 3:
      setPlantConditions(250, 15, 20, 70, 85, 400, 4500, 150000);
      break;  // Carrot
    case 4:
      setPlantConditions(250, 15, 20, 70, 85, 400, 1000, 1000);
      break; // For test
    default:
      Serial.println("Invalid plant type");
  }
}

void readTime() {
  sensorValues.seconds = millis() / 1000;

  if (sensorValues.seconds == 60) {
    sensorValues.minutes += 1;
    sensorValues.seconds = 0;
  }
  if (sensorValues.minutes == 60) {
    sensorValues.hours += 1;
    sensorValues.minutes = 0;
  }
  if (sensorValues.hours == 24) {
    sensorValues.hours = 0;
  }
}


void readSensors() {
  dhtSensor.read();

  sensorValues.soilHumidity = analogRead(HUMIDITY_SENSOR_PIN);
  sensorValues.lightIntensity = analogRead(LIGHT_SENSOR_PIN);
  sensorValues.airTemperature = dhtSensor.getTemperatureC();
  sensorValues.airHumidity = dhtSensor.getHumidity();
}


void regulateVentilation() {
  systemState.ventilationTime += CHECK_INTERVAL * 1000;
  if (sensorValues.minutes % 10 == 0) {
    systemState.regularVentilation = ON_STATE;
    systemState.ventilationTime = 0;
  } else {
    if (systemState.ventilationTime > plantConditions.ventilationDuration) {
      systemState.regularVentilation = ON_STATE;
    } else {
      systemState.regularVentilation = OFF_STATE;
    }
  }
}


void regulateTemperature() {
  if (sensorValues.airTemperature >= plantConditions.minTemperature &&
      sensorValues.airTemperature <= plantConditions.maxTemperature) {
    systemState.ventilationOn = OFF_STATE;
    systemState.heaterOn = OFF_STATE;
  }
  if (sensorValues.airTemperature < plantConditions.minTemperature) {
    systemState.ventilationOn = ON_STATE;
    systemState.heaterOn = ON_STATE;
  }
  if (sensorValues.airTemperature > plantConditions.maxTemperature) {
    systemState.ventilationOn = ON_STATE;
    systemState.heaterOn = OFF_STATE;
  }
}


void regulateHumidity() {
  if (sensorValues.airHumidity >= plantConditions.minAirHumidity &&
      sensorValues.airHumidity <= plantConditions.maxAirHumidity) {
    systemState.ventilationOn = OFF_STATE;
    systemState.pumpOn = OFF_STATE;
  }
  if (sensorValues.airHumidity < plantConditions.minAirHumidity) {
    systemState.ventilationOn = OFF_STATE;
    systemState.pumpOn = ON_STATE;
  }
  if (sensorValues.airHumidity > plantConditions.maxAirHumidity) {
    systemState.ventilationOn = ON_STATE;
    systemState.pumpOn = OFF_STATE;
  }
}


void regulateSoilHumidity() {
  if (sensorValues.soilHumidity <= plantConditions.soilHumidityThreshold) {
    systemState.pumpOn = ON_STATE;
  } else {
    systemState.pumpOn = OFF_STATE;
  }
}


void regulateLight() {
  if (sensorValues.lightIntensity <= plantConditions.lightThreshold) {
    systemState.lightOn = ON_STATE;
  } else {
    systemState.lightOn = OFF_STATE;
  }
}


void checkDayNight() {
  if (sensorValues.hours < 6 || sensorValues.hours > 22) {
    systemState.regularVentilation = OFF_STATE;
    systemState.lightOn = OFF_STATE;
  }
}


void operateLight() { digitalWrite(LIGHT_PIN, systemState.lightOn); }


void operateHeater() {
  if (systemState.heaterOn == ON_STATE) {
    digitalWrite(VENT_PIN, ON_STATE);
    digitalWrite(VENT_HEAT_PIN, ON_STATE);
  } else {
    digitalWrite(VENT_HEAT_PIN, OFF_STATE);
  }
}


void operateVentilation() {
  if (systemState.regularVentilation == ON_STATE) {
    digitalWrite(VENT_PIN, ON_STATE);
  } else if (systemState.ventilationOn == ON_STATE) {
    digitalWrite(VENT_PIN, ON_STATE);
  } else {
    digitalWrite(VENT_PIN, OFF_STATE);
  }
}


void operatePump() {
  if (systemState.lastWatering > (300000)) {
    if (systemState.pumpOn == ON_STATE) {
      digitalWrite(WATER_PUMP_PIN, systemState.pumpOn);
      systemState.wateringTime += CHECK_INTERVAL * 1000;
      if (systemState.wateringTime > plantConditions.wateringDuration) {
        digitalWrite(WATER_PUMP_PIN, OFF_STATE);
        systemState.wateringTime = 0;
        systemState.lastWatering = 0;
      }
    } else {
      digitalWrite(WATER_PUMP_PIN, OFF_STATE);
    }
  }
  systemState.lastWatering += CHECK_INTERVAL * 1000;
}


void systemCheck() {
  readSensors();

  regulateTemperature();
  regulateHumidity();
  regulateVentilation();
  regulateSoilHumidity();
  regulateLight();

  // checkDayNight();

  operateLight();
  operateVentilation();
  operateHeater();
  operatePump();
}


void loop() {
  readTime();
  if (sensorValues.seconds % CHECK_INTERVAL == 0) {
    systemCheck();
  }
}

#include <TroykaDHT.h>

#define LIGHT_SENSOR_PIN      A0
#define LIGHT_PIN             6
#define HUMIDITY_SENSOR_PIN   A1
#define WATER_PUMP_PIN        5
#define DHT_SENSOR_PIN        2
#define VENT_HEAT_PIN         4
#define VENT_PIN              7
#define ON_STATE              HIGH
#define OFF_STATE             LOW
#define POMP_INTERVAL         60000
#define VENT_INTERVAL         60000 

DHT dhtSensor(DHT_SENSOR_PIN, DHT21);

int CHECK_INTERVAL = 1; // seconds

struct SystemState {
  long long int lastVentilation;
  long long int ventilationTime;
  long long int wateringTime;
  long long int lastWatering;
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
  long long int wateringDuration;
  long long int ventilationDuration;
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
      "Type of plant 1 to 4 (1: Strawberry, 2: Cucumber, 3: Carrot, 4: Potato)");
  while (!Serial.available()) {
  }  // Wait for input
  plantType = Serial.parseInt();
  Serial.println(plantType);

  setPlantType(plantType);
}

void loop() {
  readTime();
  if (sensorValues.seconds % CHECK_INTERVAL == 0) {
    systemCheck();
  }
}

void setPlantConditions(int lightThreshold, double minTemperature,
                        double maxTemperature, double minAirHumidity,
                        double maxAirHumidity, int soilHumidityThreshold,
                        long long int wateringDuration, long long int ventilationDuration) {
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
      setPlantConditions(400, 20, 30, 50, 80, 500, 10000, 120000); 
      break;  
    case 2:
      setPlantConditions(200, 10, 25, 60, 90, 300, 15000, 180000);
      break;  
    case 3:
      setPlantConditions(250, 15, 20, 70, 85, 400, 12000, 150000);
      break;  
    case 4:
      setPlantConditions(250, -5, 50, 70, 85, 400, 50000, 30000);
      break; 
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
  delay(100);
  sensorValues.soilHumidity = analogRead(HUMIDITY_SENSOR_PIN);
  sensorValues.lightIntensity = analogRead(LIGHT_SENSOR_PIN);
  sensorValues.airTemperature = dhtSensor.getTemperatureC();
  sensorValues.airHumidity = dhtSensor.getHumidity();
}

void regulateVentilation() {
  Serial.println("============");
  Serial.println((long int)systemState.ventilationTime);
  Serial.println((long int)plantConditions.ventilationDuration);
  if (systemState.lastVentilation >= plantConditions.ventilationDuration) {
    systemState.ventilationOn = ON_STATE;
  } else {
    systemState.ventilationOn = OFF_STATE;
  }
}



void regulateTemperature() {
  if (sensorValues.airTemperature >= plantConditions.minTemperature &&
      sensorValues.airTemperature <= plantConditions.maxTemperature) {
    systemState.ventilationOn = OFF_STATE;
    systemState.heaterOn = OFF_STATE;
  }
  else if (sensorValues.airTemperature < plantConditions.minTemperature) {
    systemState.ventilationOn = ON_STATE;
    systemState.heaterOn = ON_STATE;
  }
  else if (sensorValues.airTemperature > plantConditions.maxTemperature) {
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
  if (sensorValues.soilHumidity >= plantConditions.soilHumidityThreshold) {
    systemState.pumpOn = ON_STATE;
  } else {
    systemState.pumpOn = OFF_STATE;
  }
}

void regulateLight() {
  if (sensorValues.lightIntensity >= plantConditions.lightThreshold) {
    systemState.lightOn = ON_STATE;
  } else {
    systemState.lightOn = OFF_STATE;
  }
}

void operateLight() {
  digitalWrite(LIGHT_PIN, systemState.lightOn);
}

void operateHeater() {
  if (systemState.heaterOn == ON_STATE) {
    digitalWrite(VENT_PIN, ON_STATE);
    digitalWrite(VENT_HEAT_PIN, ON_STATE);
  } else {
    digitalWrite(VENT_HEAT_PIN, OFF_STATE);
  }
}

void operateVentilation() {
  if (systemState.lastVentilation > (VENT_INTERVAL)) {
    if (1) {
      systemState.ventilationTime += CHECK_INTERVAL * 1000;
      digitalWrite(VENT_PIN, ON_STATE);
      if (systemState.ventilationTime > plantConditions.ventilationDuration) {
        digitalWrite(VENT_PIN, OFF_STATE);
        systemState.ventilationTime = 0;
        systemState.lastVentilation = 0;
      }
    } else {
      digitalWrite(VENT_PIN, systemState.ventilationOn);
    }
  }
  systemState.lastVentilation += CHECK_INTERVAL * 1000;
}

void operatePump() {
  if (systemState.lastWatering > (POMP_INTERVAL)) {
    if (systemState.pumpOn == ON_STATE) {
      digitalWrite(WATER_PUMP_PIN, systemState.pumpOn);
      systemState.wateringTime += CHECK_INTERVAL * 1000;
      if (systemState.wateringTime > plantConditions.wateringDuration) {
        digitalWrite(WATER_PUMP_PIN, OFF_STATE);
        systemState.wateringTime = 0;
        systemState.lastWatering = 0;
      }
    } else {
      digitalWrite(WATER_PUMP_PIN, systemState.pumpOn);
    }
  }
  systemState.lastWatering += CHECK_INTERVAL * 1000;
}

void systemCheck() {
  readSensors();
  regulateTemperature();
  regulateHumidity();
//  regulateVentilation();
  regulateSoilHumidity();
  regulateLight();
  operateLight();
  operateVentilation();
  operateHeater();
  operatePump();
}

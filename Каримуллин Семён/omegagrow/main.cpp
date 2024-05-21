#include <Arduino.h>
#include <TroykaDHT.h>
#include <avr/interrupt.h>

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

#define NOTE_B0  31

#define NOTE_C1  33

#define NOTE_CS1 35

#define NOTE_D1  37

#define NOTE_DS1 39

#define NOTE_E1  41

#define NOTE_F1  44

#define NOTE_FS1 46

#define NOTE_G1  49

#define NOTE_GS1 52

#define NOTE_A1  55

#define NOTE_AS1 58

#define NOTE_B1  62

#define NOTE_C2  65

#define NOTE_CS2 69

#define NOTE_D2  73

#define NOTE_DS2 78

#define NOTE_E2  82

#define NOTE_F2  87

#define NOTE_FS2 93

#define NOTE_G2  98

#define NOTE_GS2 104

#define NOTE_A2  110

#define NOTE_AS2 117

#define NOTE_B2  123

#define NOTE_C3  131

#define NOTE_CS3 139

#define NOTE_D3  147

#define NOTE_DS3 156

#define NOTE_E3  165

#define NOTE_F3  175

#define NOTE_FS3 185

#define NOTE_G3  196

#define NOTE_GS3 208

#define NOTE_A3  220

#define NOTE_AS3 233

#define NOTE_B3  247

#define NOTE_C4  262

#define NOTE_CS4 277

#define NOTE_D4  294

#define NOTE_DS4 311

#define NOTE_E4  330

#define NOTE_F4  349

#define NOTE_FS4 370

#define NOTE_G4  392

#define NOTE_GS4 415

#define NOTE_A4  440

#define NOTE_AS4 466

#define NOTE_B4  494

#define NOTE_C5  523

#define NOTE_CS5 554

#define NOTE_D5  587

#define NOTE_DS5 622

#define NOTE_E5  659

#define NOTE_F5  698

#define NOTE_FS5 740

#define NOTE_G5  784

#define NOTE_GS5 831

#define NOTE_A5  880

#define NOTE_AS5 932

#define NOTE_B5  988

#define NOTE_C6  1047

#define NOTE_CS6 1109

#define NOTE_D6  1175

#define NOTE_DS6 1245

#define NOTE_E6  1319

#define NOTE_F6  1397

#define NOTE_FS6 1480

#define NOTE_G6  1568

#define NOTE_GS6 1661

#define NOTE_A6  1760

#define NOTE_AS6 1865

#define NOTE_B6  1976

#define NOTE_C7  2093

#define NOTE_CS7 2217

#define NOTE_D7  2349

#define NOTE_DS7 2489

#define NOTE_E7  2637

#define NOTE_F7  2794

#define NOTE_FS7 2960

#define NOTE_G7  3136

#define NOTE_GS7 3322

#define NOTE_A7  3520

#define NOTE_AS7 3729

#define NOTE_B7  3951

#define NOTE_C8  4186

#define NOTE_CS8 4435

#define NOTE_D8  4699

#define NOTE_DS8 4978

DHT dhtSensor(DHT_SENSOR_PIN, DHT21);

int CHECK_INTERVAL = 1; // seconds

int melody[] = {
  NOTE_C6, NOTE_G5, NOTE_E5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5,
  NOTE_C6, NOTE_G5, NOTE_E5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5,
  NOTE_C6, NOTE_G5, NOTE_E5, NOTE_A5
};

int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 4
};

volatile int melodyIndex = 0;
volatile boolean playing = false;
const size_t note_count = sizeof(melody) / sizeof(melody[0]);

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

ISR(TIMER1_COMPA_vect) {
  int noteDuration = 1000 / noteDurations[melodyIndex];
  tone(13, melody[melodyIndex], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  
  melodyIndex++;  
  
  if (melodyIndex >= sizeof(melody) / sizeof(melody[0])) {
    melodyIndex = 0; // Перезапуск мелодии после завершения
    playing = false;
    noTone(13);
  }
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

void setup() {
  Serial.begin(9600);
  dhtSensor.begin();
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(DHT_SENSOR_PIN, INPUT);
  pinMode(VENT_HEAT_PIN, OUTPUT);
  pinMode(VENT_PIN, OUTPUT);
  cli(); // Отключаем прерывания
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 4000; // Значение для достижения частоты прерываний в 1 секунду
  TCCR1B |= (1 << WGM12); // Режим CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // Предделитель на 1024
  TIMSK1 |= (1 << OCIE1A); // Включаем прерывание по совпадению с OCR1A
  sei(); // Включаем прерывания

  int plantType;
  Serial.println(
      "Enter plant type (1: Strawberry, 2: Cucumber, 3: Carrot, 4: Test)");
  while (!Serial.available()) {
  }  // Wait for input
  plantType = Serial.parseInt();
  Serial.println(plantType);

  setPlantType(plantType);
}

void loop() {
  if (!playing) {
    playing = true;
    melodyIndex = 0;
  }
  readTime();
  if (sensorValues.seconds % CHECK_INTERVAL == 0) {
    systemCheck();
  }
}
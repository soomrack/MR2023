// output
#define FAN_PIN		   7
#define LED_PIN		   6
#define WATER_PUMP_PIN 5
#define HEAT_PIN	   4

// input
#define SENSOR_DHT_PIN		2
#define SENSOR_LED_PIN		0
#define SENSOR_HUMIDITY_PIN 1

// libraries
#include <TroykaDHT.h>
#include "Narcoleptic.h"
DHT dht_sensor(SENSOR_DHT_PIN, DHT21);

// conditions
#define MIN_LIGHT		   600
#define MIN_TEMPERATURE	   15.0
#define MAX_TEMPERATURE	   40.0
#define MIN_HUMIDITY	   60
#define WATERING_FREQUENCY 60

// digital constants
#define TEN_MINUTES	 600000
#define TEN_SECONDS	 10000
#define FIVE_SECONDS 5000

// control variables
unsigned long int last_action_time = millis();
bool			  all_conditions_correct = true;

void setup()
{
	Serial.begin(9600);
	dht_sensor.begin();

	// output
	pinMode(FAN_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);
	pinMode(WATER_PUMP_PIN, OUTPUT);
	pinMode(HEAT_PIN, OUTPUT);

	// input
	pinMode(SENSOR_DHT_PIN, INPUT);
	pinMode(SENSOR_LED_PIN, INPUT);		 // [1:1023] 1023 - night
	pinMode(SENSOR_HUMIDITY_PIN, INPUT); // [1:1023] 1023 - dry
}

void loop()
{
	// real work
	conditions_correct();
	if (check_temperature()) {
	conditions_incorrect();
	if (check_cold()) {
		turn_on_heater();
		turn_on_fan();
	}
	if (check_hot()) {
		conditions_incorrect();
		turn_on_fan();
	}
	} else {
	turn_off_heater();
	turn_off_fan();
	};
	if (time_for_watering() || check_humidity()) {
	conditions_incorrect();
	turn_on_watering();
	}
	if (check_illumination()) {
	turn_on_light();
	} else {
	turn_off_light();
	};
	if (all_conditions_correct) {
	delay_ten_minutes();
	}
	delay_ten_seconds();

	// test

	turn_on_light();
}

// ********** Check conditions **********

bool check_temperature()
{
	float temperature;
	switch (dht_sensor.getState())
	{
		case DHT_OK:
			temperature = dht_sensor.getTemperatureC();
			return (temperature < MIN_TEMPERATURE) || (temperature > MAX_TEMPERATURE);
		default:
			Serial.println("Something wrong");
	}
}

bool check_cold()
{
	float temperature;
	dht_sensor.read();
	switch (dht_sensor.getState())
	{
		case DHT_OK:
			temperature = dht_sensor.getTemperatureC();
			return temperature < MIN_TEMPERATURE;
		default:
			Serial.println("Something wrong");
	}
}

bool check_hot()
{
	float temperature;
	dht_sensor.read();
	switch (dht_sensor.getState())
	{
		case DHT_OK:
			temperature = dht_sensor.getTemperatureC();
			return temperature > MAX_TEMPERATURE;
		default:
			Serial.println("Something wrong");
	}
}

bool check_humidity()
{
	byte humidity = digitalRead(SENSOR_HUMIDITY_PIN);
	return humidity < MIN_HUMIDITY;
}

bool check_illumination()
{
	bool is_dark = digitalRead(SENSOR_LED_PIN);
	return is_dark;
}

bool time_for_watering()
{
	if (millis() - last_action_time > TEN_MINUTES)
	{
		last_action_time = millis();
		return true;
	}
	else
	{
		return false;
	}
}

// ********** Greenhouse parameters control **********

void turn_on_light()
{
	digitalWrite(LED_PIN, HIGH);
}

void turn_off_light()
{
	digitalWrite(LED_PIN, LOW);
}

void turn_on_heater()
{
	digitalWrite(HEAT_PIN, HIGH);
}

void turn_off_heater()
{
	digitalWrite(HEAT_PIN, LOW);
}

void turn_on_fan()
{
	digitalWrite(FAN_PIN, HIGH);
}

void turn_off_fan()
{
	digitalWrite(FAN_PIN, LOW);
}

void turn_on_watering()
{
	digitalWrite(WATER_PUMP_PIN, HIGH);
	Narcoleptic.delay(TEN_SECONDS); // Watering time
	digitalWrite(WATER_PUMP_PIN, LOW);
	Narcoleptic.delay(TEN_MINUTES); // Waiting for the water to spread
}

// ********** Delay functions **********

void delay_ten_minutes()
{
	Narcoleptic.delay(TEN_MINUTES);
}

void delay_ten_seconds()
{
	Narcoleptic.delay(TEN_SECONDS);
}

void delay_five_seconds()
{
	Narcoleptic.delay(FIVE_SECONDS);
}

// ********** Is conditions correct **********

void conditions_incorrect()
{
	all_conditions_correct = false;
}

void conditions_correct()
{
	all_conditions_correct = true;
}

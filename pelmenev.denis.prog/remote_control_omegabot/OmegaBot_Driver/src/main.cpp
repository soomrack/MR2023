#include "driver.hpp"

Driver Wheels(6, 5, 7, 4, A1, A2, 200);  // Инициализация с пинами для моторов

void setup() {
    Serial.begin(9600);
    delay(3000);
    Serial.println("Arduino started. Logging initialized...");
}

void loop() {
    char command = Wheels.read_command();
    if (command != '0') { 
        unsigned long currentMillis = millis();

        Wheels.get_command_arm(command);
        Wheels.get_command_wheels(command);
        Wheels.get_command_other(command);

        Wheels.write_logs(command, currentMillis);

        Wheels.clear_serial_buffer();
    }
}

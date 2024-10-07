#ifndef SENSORDATA_HPP
#define SENSORDATA_HPP

#include <mutex>
#include <tuple>

class SensorData {
public:
    static int sensor_values[2];  
    static std::mutex data_mutex; 

    static void setValues(int forward_value, int left_value) {
        std::lock_guard<std::mutex> lock(data_mutex); 
        sensor_values[0] = forward_value; 
        sensor_values[1] = left_value;
    }

    static std::tuple<int, int> getValues() {
        std::lock_guard<std::mutex> lock(data_mutex);
        return std::make_tuple(sensor_values[0], sensor_values[1]);
    }
};

int SensorData::sensor_values[2] = {0, 0};
std::mutex SensorData::data_mutex;

#endif // SENSORDATA_HPP

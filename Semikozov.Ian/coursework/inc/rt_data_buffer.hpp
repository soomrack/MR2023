/**
 * @file rt_data_buffer.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 04.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef RT_DATA_BUFFER_HPP_INCLUDED
#define RT_DATA_BUFFER_HPP_INCLUDED

#include <cstring>
#include <memory>
#include <mutex>

#include "protocol.hpp"

class RTDataBuffer
{
public:
    RTDataBuffer() = default;

    inline void get(Message::ServerData *p) const
    {
        std::memcpy(p->standAngles, this->standAngles, sizeof(standAngles));

        std::lock_guard<std::mutex> lock(m);
        std::memcpy(p->adcRawValue, this->adcRawValue, sizeof(adcRawValue));
    }

    void setAzimuth(float angle) { standAngles[0] = angle; }

    void setElevation(float angle) { standAngles[1] = angle; }

    void setAdc(int16_t *data)
    {
        std::lock_guard<std::mutex> lock(m);
        std::memcpy(adcRawValue, data, sizeof(adcRawValue));
    }

private:
    void calculate();

private:
    mutable std::mutex m;
    float adcRawValue[4];
    float standAngles[2];
};

#endif // RT_DATA_BUFFER_HPP_INCLUDED

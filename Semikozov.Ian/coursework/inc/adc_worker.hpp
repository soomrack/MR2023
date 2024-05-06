/**
 * @file adc_worker.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 30.03.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef ADC_WORKER_HPP_INCLUDED
#define ADC_WORKER_HPP_INCLUDED

#include <boost/signals2.hpp>
#include <condition_variable>
#include <cstring>
#include <unordered_map>

#include "ADS1115.h"
#include "rt_data_buffer.hpp"
#include "unix.h"
#include "worker_base.hpp"

using FSR = ADS1115::FullScaleRange;

template <typename T>
class Test
{
public:
    Test();
    ~Test();
    void test();
};

enum Mode : uint8_t
{
    SingleShot,
    Loop
};

class ADCWorker : public WorkerBase
{
    static constexpr const char *kDefaultDevice{ "/dev/i2c-1" };
    static constexpr std::uint8_t kDefaultAddress{ 0x48 };
    static constexpr size_t kChannelCount{ 4 };
    static constexpr size_t kDefaultSWSPS{ 10 };
    static constexpr FSR kDefaultFSR{ FSR::FSR_0_256V };
    static constexpr bool kSilent{ true };

public:
    ADCWorker(RTDataBuffer *buffer = nullptr);
    ~ADCWorker();

    void handle(std::unique_ptr<Message::ClientData> &payload) override;
    void get(std::shared_ptr<std::uint8_t[]> &p) const override;
    void swSingleShot(size_t sps);

public:
    boost::signals2::signal<void(const float *mean)> signal;

private:
    size_t sw_sps{ kDefaultSWSPS };
    ADS1115::ADC<unix_i2c::i2c> adc;
    std::int16_t raw[kChannelCount];
    float mean_raw[kChannelCount];
    std::unordered_map<int, ADS1115::Multiplex> muxs;
    std::condition_variable cv;
    std::atomic_bool update{ false };

private:
    void prestart() override;
    ADS1115::Error readMux(ADS1115::Multiplex mux, std::int16_t &raw);
    ADS1115::Error readAll(std::int16_t *raw);

protected:
    void run() override;
};

#endif // ADC_WORKER_HPP_INCLUDED

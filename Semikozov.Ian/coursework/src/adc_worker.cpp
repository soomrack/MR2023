#include "adc_worker.hpp"
#include "protocol.hpp"

template class Test<int>;

template <typename T>
Test<T>::Test()
{}

template <typename T>
Test<T>::~Test()
{}

template <typename T>
void Test<T>::test()
{}

ADCWorker::ADCWorker(RTDataBuffer *buffer) : WorkerBase(ID::ADS), adc(kDefaultDevice, kDefaultAddress)
{
    this->buffer = buffer;

    muxs[0] = ADS1115::Multiplex::AIN0;
    muxs[1] = ADS1115::Multiplex::AIN1;
    muxs[2] = ADS1115::Multiplex::AIN2;
    muxs[3] = ADS1115::Multiplex::AIN3;

    auto config_fsr = ADS1115::FullScaleRange::FSR_0_256V;
    auto config_dr = ADS1115::DataRate::SPS_860;
    auto config_mode = ADS1115::ConversionMode::SingleShot;

    adc.setFsr(config_fsr);
    adc.setDataRate(config_dr);
    adc.setConversionMode(config_mode);
}

ADCWorker::~ADCWorker()
{
    if (enable) { this->stop(); }
}

void ADCWorker::handle(std::unique_ptr<Message::ClientData> &payload)
{
    using namespace Message;
    using namespace Commands;

    std::cout << "[info] | ADCWorker: Received command - " << payload->command.adsCommand << " with main payload " << payload->main[0] << " and " << payload->main[1]
              << " and common " << static_cast<int>(payload->common) << std::endl;

    switch (payload->command.adsCommand)
    {
        case ADC::SetFSR:
        {
            auto fsr = static_cast<const FSR>(payload->main[0]);
            adc.setFsr(fsr);
            break;
        }

        case ADC::ReadAllMuxs:
        {
            this->swSingleShot(static_cast<size_t>(payload->main[0]));
            break;
        }

        default: break;
    }
}

void ADCWorker::get(std::shared_ptr<std::uint8_t[]> &p) const
{
    std::lock_guard<std::mutex> lock(m);
    std::memcpy(p.get(), mean_raw, sizeof(raw));
}

void ADCWorker::prestart()
{
    auto config_fsr = ADS1115::FullScaleRange::FSR_0_256V;
    adc.setFsr(config_fsr);
}

ADS1115::Error ADCWorker::readMux(ADS1115::Multiplex mux, std::int16_t &raw)
{
    auto err = adc.read(mux, raw);

    if (!kSilent)
    {
        std::cout << "[info] | ADCWorker: Reading multiplexer " << mux << " = " << raw << " POPUG" << std::endl;
        std::cout << "[info] | ADCWorker: Current status code = " << static_cast<int>(err) << std::endl;
    }

    return err;
}

void ADCWorker::swSingleShot(size_t sps)
{
    sw_sps = sps;

    std::unique_lock<std::mutex> lock(m);

    static int32_t temp[4] = { 0 };

    for (int i = 0; i < sps; i++)
    {
        std::cout << "[info] | ADCWorker: Reading: " << i << std::endl;
        if (this->readAll(raw))
        {
            signal(nullptr);
            return;
        }
        for (int j = 0; j < 4; j++) { temp[j] += raw[j]; }
    }

    for (int j = 0; j < 4; j++) { mean_raw[j] = static_cast<float>(temp[j]) / sw_sps; }

    signal(mean_raw);

    std::memset(temp, 0, sizeof(temp));
}

ADS1115::Error ADCWorker::readAll(std::int16_t *raw)
{
    ADS1115::Error err;
    for (auto mux : muxs) { err = this->readMux(mux.second, raw[mux.first]); }
    return err;
}

void ADCWorker::run()
{
    static int32_t temp[4] = { 0 };

    while (enable)
    {
        std::unique_lock<std::mutex> lock(m);

        if (!update) { continue; }
        while (!m.try_lock()) {}
        this->readAll(raw);

        if (buffer) { buffer->setAdc(raw); }

        m.unlock();
    }
}

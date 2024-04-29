#pragma once

#ifdef __unix__
#define ADS1115_STREAM_OP 1
#else
#define ADS1115_STREAM_OP 0
#endif

#include <string>

#if ADS1115_STREAM_OP
#include <iostream>
#endif

#include <cstdint>

#include "error.h"

namespace ADS1115
{
enum RegisterAddress : uint8_t
{
    Conversion = 0b00,
    Config = 0b01,
    Lo_thresh = 0b10,
    Hi_thresh = 0b11,
};

enum AddressPin : uint8_t
{
    GND = 0b1001000,
    VDD = 0b1001001,
    SDA = 0b1001010,
    SCL = 0b1001011,
};

enum FullScaleRange : uint16_t
{
    FSR_6_144V = (0b000) << 9,  // : FSR = ±6.144 V(1)
    FSR_4_096V = (0b001) << 9,  // : FSR = ±4.096 V(1)
    FSR_2_048V = (0b010) << 9,  // : FSR = ±2.048 V (default)
    FSR_1_024V = (0b011) << 9,  // : FSR = ±1.024 V
    FSR_0_512V = (0b100) << 9,  // : FSR = ±0.512 V
    FSR_0_256V = (0b101) << 9,  // : FSR = ±0.256 V
    FSR_0_256V1 = (0b110) << 9, // : FSR = ±0.256 V
    FSR_0_256V2 = (0b111) << 9, // : FSR = ±0.256 V
};

enum Multiplex : uint16_t
{
    AIN0_AIN1 = (0b000) << 12, // : AINP = AIN0 and AINN = AIN1 (default)
    AIN0_AIN3 = (0b001) << 12, // : AINP = AIN0 and AINN = AIN3
    AIN1_AIN3 = (0b010) << 12, // : AINP = AIN1 and AINN = AIN3
    AIN2_AIN3 = (0b011) << 12, // : AINP = AIN2 and AINN = AIN3
    AIN0 = (0b100) << 12,      // : AINP = AIN0 and AINN = GND
    AIN1 = (0b101) << 12,      // : AINP = AIN1 and AINN = GND
    AIN2 = (0b110) << 12,      // : AINP = AIN2 and AINN = GND
    AIN3 = (0b111) << 12,      // : AINP = AIN3 and AINN = GND
};

enum DataRate : uint16_t
{
    SPS_8 = (0b000) << 5,   // : 8 SPS
    SPS_16 = (0b001) << 5,  // : 16 SPS
    SPS_32 = (0b010) << 5,  // : 32 SPS
    SPS_64 = (0b011) << 5,  // : 64 SPS
    SPS_128 = (0b100) << 5, // : 128 SPS (default)
    SPS_250 = (0b101) << 5, // : 250 SPS
    SPS_475 = (0b110) << 5, // : 475 SPS
    SPS_860 = (0b111) << 5, // : 860 SPS
};

/**
 * @brief Comparator queue
 *
 * @details
 *          These bits perform two functions. When set to 11, the comparator is
 *          disabled and the ALERT/RDY pin is set to a high-impedance state.
 *          When set to any other value, the ALERT/RDY pin and the comparator
 *          function are enabled, and the set value determines the number of
 *          successive conversions exceeding the upper or lower threshold
 *          required before asserting the ALERT/RDY pin. These bits serve no
 *          function on the ADS1113.
 */
enum ComparatorQueue : uint16_t
{
    ONE_CONVERSION = 0b00,   //! Assert after one conversion
    TWO_CONVERSIONS = 0b01,  //! Assert after two conversions
    FOUR_CONVERSIONS = 0b10, //! Assert after four conversions
    DISABLE = 0b11,          //! Disable comparator and set ALERT/RDY pin to high-impedance (default)
};

enum ConversionMode : uint16_t
{
    Continuous = 0,
    SingleShot = (1 << 8),
};

enum Config : uint16_t
{
    OS = (1 << 15),                 /*
                                     * When writing: 0 : No effect 1 : Start a single conversion (when in
                                     * power-down state).  When reading: 0 : Device is currently
                                     * performing a conversion 1 : Device is not currently performing a
                                     * conversion
                                     */
    COMPARATOR_MODE = (1 << 4),     /*
                                     * Comparator mode (ADS1114 and ADS1115 only) This bit configures the
                                     * comparator operating mode. This bit serves no function on the
                                     * ADS1113. 0 : Traditional comparator (default) 1 : Window comparator
                                     */
    COMPARATOR_POL = (1 << 3),      /*
                                     * Comparator polarity(ADS1114 and ADS1115 only) This bit controls the
                                     * polarity of the ALERT pin.This bit serves no function on the
                                     * ADS1113. 0 : Active low(default)
                                     */
    COMPARATOR_LATCHING = (1 << 2), /*
                                     * Latching comparator (ADS1114 and ADS1115 only) This bit controls
                                     * whether the ALERT/RDY pin latches after being asserted or clears
                                     * after conversions are within the margin of the upper and lower
                                     * threshold values. This bit serves no function on the ADS1113. 0 :
                                     * Nonlatching comparator . The ALERT/RDY pin does not latch when
                                     * asserted (default). 1 : Latching comparator. The asserted
                                     * ALERT/RDY pin remains latched until conversion data are read by
                                     * the master or an appropriate SMBus alert response is sent by the
                                     * master. The device responds with its address, and it is the
                                     * lowest address currently asserting the ALERT/RDY bus line.
                                     */
};
#if ADS1115_STREAM_OP
//     std::unordered_map<ADS1115::FullScaleRange, std::string> fsrToString = {
//     {ADS1115::FullScaleRange::FSR_6_144V, "6.144V"},
//     {ADS1115::FullScaleRange::FSR_4_096V, "4.096V"},
//     {ADS1115::FullScaleRange::FSR_2_048V, "2.048V"},
//     {ADS1115::FullScaleRange::FSR_1_024V, "1.024V"},
//     {ADS1115::FullScaleRange::FSR_0_512V, "0.512V"}
// };

// std::unordered_map<ADS1115::Multiplex, std::string> multiplexToString = {
//     {ADS1115::Multiplex::AIN0_AIN1, "AIN0_AIN1"},
//     {ADS1115::Multiplex::AIN0_AIN3, "AIN0_AIN3"},
//     {ADS1115::Multiplex::AIN1_AIN3, "AIN1_AIN3"},
//     {ADS1115::Multiplex::AIN2_AIN3, "AIN2_AIN3"},
//     {ADS1115::Multiplex::AIN0, "AIN0"},
//     {ADS1115::Multiplex::AIN1, "AIN1"},
//     {ADS1115::Multiplex::AIN2, "AIN2"},
//     {ADS1115::Multiplex::AIN3, "AIN3"}
// };

// std::unordered_map<ADS1115::DataRate, std::string> dataRateToString = {
//     {ADS1115::DataRate::SPS_8, "8"},
//     {ADS1115::DataRate::SPS_16, "16"},
//     {ADS1115::DataRate::SPS_32, "32"},
//     {ADS1115::DataRate::SPS_64, "64"},
//     {ADS1115::DataRate::SPS_128, "128"},
//     {ADS1115::DataRate::SPS_250, "250"},
//     {ADS1115::DataRate::SPS_475, "475"},
//     {ADS1115::DataRate::SPS_860, "860"}
// };

// std::unordered_map<ADS1115::ConversionMode, std::string> conversionModeToString = {
//     {ADS1115::ConversionMode::Continuous, "Continuous"},
//     {ADS1115::ConversionMode::SingleShot, "Single Shot"}
// };
// ADS1115::FullScaleRange fsr = ADS1115::FullScaleRange::FSR_4_096V;
// ADS1115::Multiplex multiplexer = ADS1115::Multiplex::AIN1_AIN3;
// ADS1115::DataRate dataRate = ADS1115::DataRate::SPS_128;
// ADS1115::ConversionMode mode = ADS1115::ConversionMode::Continuous;
inline std::ostream &operator<<(std::ostream &os, const FullScaleRange &fsr)
{
    switch (fsr)
    {
        case FullScaleRange::FSR_6_144V: os << "6.144V"; break;
        case FullScaleRange::FSR_4_096V: os << "4.096V"; break;
        case FullScaleRange::FSR_2_048V: os << "2.048V"; break;
        case FullScaleRange::FSR_1_024V: os << "1.024V"; break;
        case FullScaleRange::FSR_0_512V: os << "0.512V"; break;
        default: os << "0.256V"; break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const Multiplex &multi)
{
    switch (multi)
    {
        case Multiplex::AIN0_AIN1: os << "AIN0_AIN1"; break;
        case Multiplex::AIN0_AIN3: os << "AIN0_AIN3"; break;
        case Multiplex::AIN1_AIN3: os << "AIN1_AIN3"; break;
        case Multiplex::AIN2_AIN3: os << "AIN2_AIN3"; break;
        case Multiplex::AIN0: os << "AIN0"; break;
        case Multiplex::AIN1: os << "AIN1"; break;
        case Multiplex::AIN2: os << "AIN2"; break;
        case Multiplex::AIN3: os << "AIN3"; break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const DataRate &dr)
{
    switch (dr)
    {
        case DataRate::SPS_8: os << "8"; break;
        case DataRate::SPS_16: os << "16"; break;
        case DataRate::SPS_32: os << "32"; break;
        case DataRate::SPS_64: os << "64"; break;
        case DataRate::SPS_128: os << "128"; break;
        case DataRate::SPS_250: os << "250"; break;
        case DataRate::SPS_475: os << "475"; break;
        case DataRate::SPS_860: os << "860"; break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const ConversionMode &mode)
{
    switch (mode)
    {
        case ConversionMode::Continuous: os << "Continuous"; break;
        case ConversionMode::SingleShot: os << "Single Shot"; break;
    }

    return os;
}
#endif

inline bool isValidAddress(const uint8_t address)
{
    return (address & ~0b11) == 0b1001000; // The 2 lowest pins are selectable so we need to check the upper 6 bits.
}

inline double getFsrVoltage(const FullScaleRange fsr)
{
    switch (fsr)
    {
        case FSR_6_144V: return 6.144L;
        case FSR_4_096V: return 4.096L;
        case FSR_2_048V: return 2.048L;
        case FSR_1_024V: return 1.024L;
        case FSR_0_512V: return 0.512L;
        default: return 0.256L;
    }
}

/**
 * @brief      Class for ADS1115.
 *
 * @tparam     impl_t  I2C implemention see unix.h for example (can be overwritten for stm32 or others).
 *
 */
template <class impl_t>
class ADC
{
public:
    ADC(const char *const port, const uint8_t address) : m_impl(port), m_address(address), m_config(DEFAULT_CFG) {}
    ADC(void *const port, const uint8_t address) : m_impl(port), m_address(address), m_config(DEFAULT_CFG) {}
    ADC(const uint port, const uint8_t address) : m_impl(port), m_address(address), m_config(DEFAULT_CFG) {}
    ~ADC() {}

    Error readRegister(RegisterAddress regAddress, uint16_t &reg)
    {
        uint8_t tx[1] = { static_cast<uint8_t>(regAddress) };
        uint8_t rx[2];

        auto err = m_impl.begin(m_address);

        if (err == Error::NONE) err = m_impl.write(tx, 1);

        if (err == Error::NONE) err = m_impl.read(rx, 2);

        if (err == Error::NONE) reg = (rx[0] << 8) | rx[1];

        return err;
    }

    Error writeRegister(RegisterAddress regAddress, const uint16_t value)
    {
        uint8_t tx[3] = { static_cast<uint8_t>(regAddress),
                          static_cast<uint8_t>(value >> 8),
                          static_cast<uint8_t>(value & 0xFF) };

        auto err = m_impl.begin(m_address);
        if (err == Error::NONE) err = m_impl.write(tx, 3);
        return err;
    }

    Error readConfig(uint16_t &cfg)
    {
        return readRegister(RegisterAddress::Config, cfg);
    }

    Error writeConfig(const uint16_t cfg)
    {
        return writeRegister(RegisterAddress::Config, cfg);
    }

    Error writeConfig(void)
    {
        return writeConfig(m_config);
    }

    Error writeConfigDefault(void)
    {
        return writeConfig(DEFAULT_CFG);
    }

    Error isConversionDone(bool &done)
    {
        uint16_t cfg = 0;
        const auto err = readConfig(cfg);
        done = (cfg & Config::OS) ? true : false;
        return err;
    }

    Error read(const Multiplex mux, double &val)
    {
        setMultiplexing(mux);
        return read(val);
    }

    Error read(const Multiplex mux, int16_t &val)
    {
        setMultiplexing(mux);
        const auto err = readRaw(val);
        return err;
    }

    Error read(double &val)
    {
        int16_t val_raw = 0;
        const auto err = readRaw(val_raw);
        val = rawToVoltage(val_raw);
        return err;
    }

    Error readRaw(int16_t &val)
    {
        // Conviently we can send the configuration and the conversion request in one
        // command.
        auto err = writeConfig(m_config | Config::OS);
        if (err != Error::NONE) return err;

        // Once the conversion has been requested we must wait for it do be finished.
        bool done = false;
        do {
            err = isConversionDone(done);
            if (err != Error::NONE) return err;
        }
        while (!done);

        uint16_t reg = 0;
        // The conversion register stores the latest result.
        err = readRegister(RegisterAddress::Conversion, reg);

        if (err == Error::NONE) val = static_cast<int16_t>(reg);

        return err;
    }

    void setFsr(const FullScaleRange fsr)
    {
        m_config &= ~FSR_0_256V2;
        m_config |= fsr;
    }

    void setMultiplexing(const Multiplex mult)
    {
        m_config &= ~AIN3;
        m_config |= mult;
    }

    void setDataRate(const DataRate dr)
    {
        m_config &= ~SPS_860;
        m_config |= dr;
    }

    void setConversionMode(const ConversionMode mode)
    {
        if (mode) m_config |= ConversionMode::SingleShot;
        else m_config &= ~ConversionMode::SingleShot;
    }

    const FullScaleRange getFsr(void) const
    {
        return static_cast<FullScaleRange>((m_config & FullScaleRange::FSR_0_256V2));
    }

    const Multiplex getMultiplexing(void) const
    {
        return static_cast<Multiplex>((m_config & Multiplex::AIN3));
    }

    const DataRate getDataRate(void) const
    {
        return static_cast<DataRate>((m_config & DataRate::SPS_860));
    }

    const ConversionMode getConversionMode(void) const
    {
        return static_cast<ConversionMode>(m_config & ConversionMode::SingleShot);
    }

private:
    static constexpr auto DEFAULT_CFG = 0x0583; // Default register configuration.
    impl_t m_impl;
    const uint8_t m_address; // I2C address, fixed at construction.
    uint16_t m_config;       // Packed structure of the configuration. Essentially this is the
                             // config register shadow copy.

    double rawToVoltage(const int16_t raw_value)
    {
        const auto fsr_v = getFsrVoltage(getFsr());
        return raw_value * (fsr_v / static_cast<double>(0x7FFF));
    }
};

} // namespace ADS1115

#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

#include "ADS1115.h"
#include "unix.h" //THis example relies on the unix implementaion.

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::vector;

namespace
{
template <typename T>
void readMux(ADS1115::ADC<T> &adc, ADS1115::Multiplex mux)
{
    double valVoltage;
    auto err = adc.read(mux, valVoltage);
    cout << mux << " = " << valVoltage << " V | err = " << static_cast<int>(err) << endl;
}

template <typename T>
void readRawMux(ADS1115::ADC<T> &adc, ADS1115::Multiplex mux, int16_t &rawValue)
{
    auto err = adc.read(mux, rawValue);
    cout << mux << " = " << rawValue << " V | err = " << static_cast<int>(err) << endl;
}
}; // namespace

/**
 * @brief
 *
 * @param argc the serial port or enumerate flag
 * @param argv the address of the chip in hex.
 * @param rawValue the array with 4 int16_t elements for 4 channels
 * @return int
 */
int run(int argc, char **argv, int16_t *rawValue)
{
    if (argc < 2) { throw std::runtime_error("Invalid arguments count!"); }

    // string  port(argv[1]);
    const auto port = argv[1];
    uint8_t address = std::stoul(argv[2], nullptr, 16);

    if (!ADS1115::isValidAddress(address))
    {
        cout << "Address invalid, possible addresses include: " << endl;
        cout << "\t ADR pin to GND: 0x" << std::hex << ADS1115::AddressPin::GND << endl;
        cout << "\t ADR pin to VDD: 0x" << std::hex << ADS1115::AddressPin::VDD << endl;
        cout << "\t ADR pin to SDA: 0x" << std::hex << ADS1115::AddressPin::SDA << endl;
        cout << "\t ADR pin to SCL: 0x" << std::hex << ADS1115::AddressPin::SCL << endl;
        return -1;
    }

    cout << "Openning ADS1115 at " << port << " with address: " << address << endl;

    ADS1115::ADC<unix_i2c::i2c> adc(port, address);

    auto config_fsr = ADS1115::FullScaleRange::FSR_0_256V;
    auto config_dr = ADS1115::DataRate::SPS_860;

    cout << "Setting FSR to +-" << config_fsr << endl;
    cout << "Setting DR to " << config_dr << endl;

    adc.setFsr(config_fsr);
    adc.setDataRate(config_dr);

    cout << "ADC Configuration" << endl;
    cout << "\tfsr             : " << adc.getFsr() << endl;
    cout << "\tmultiplexing    : " << adc.getMultiplexing() << endl;
    cout << "\tdata rate       : " << adc.getDataRate() << endl;
    cout << "\tconversion mode : " << adc.getConversionMode() << endl;

    readRawMux<>(adc, ADS1115::Multiplex::AIN0, rawValue[0]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN1, rawValue[1]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN2, rawValue[2]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN3, rawValue[3]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN0_AIN1, rawValue[0]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN0_AIN3, rawValue[1]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN1_AIN3, rawValue[2]);
    readRawMux<>(adc, ADS1115::Multiplex::AIN2_AIN3, rawValue[3]);

    return 0;
}

int main(int argc, char **argv)
{
    int16_t tempRawValue[4]; // absolute values of photodiodes on the bottom layer
    double x, y;

    while (true)
    {
        try
        {
            run(argc, argv, tempRawValue);
        }
        catch (exception &e)
        {
            cerr << "Unhandled Exception: " << e.what() << endl;
        }

        x = ((tempRawValue[0] + tempRawValue[2]) - (tempRawValue[1] + tempRawValue[3]));
        y = ((tempRawValue[0] + tempRawValue[1]) - (tempRawValue[2] + tempRawValue[3]));
        cout << "X = " << x << " mm | Y = " << y << " mm" << endl;
        usleep(1000000);
    }
}

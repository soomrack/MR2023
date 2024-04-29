#include "unix.h"
#include <exception>

namespace unix_i2c
{
    namespace
    {
        ADS1115::Error getError(const int err) {
            switch (err)
            {
            case 0:
                return ADS1115::Error::NONE;
            case EAGAIN:
                return ADS1115::Error::BUSY;
            case EISDIR:
            case EBADF:
            case EFAULT:
                return ADS1115::Error::BAD_ADDRESS;
            case EIO:
                return ADS1115::Error::IO;
            case EINVAL:
                return ADS1115::Error::INVALID_ARG;
            default:
                return ADS1115::Error::ERROR;
            }
        }
    }; // namespace

    i2c::i2c(const void *arg) {
        if ((m_file = open(static_cast<const char *>(arg), O_RDWR)) < 0)
            throw std::runtime_error("I2C Cannot open port ");
    }

    i2c::i2c(const char *const arg) {
        if ((m_file = open(arg, O_RDWR)) < 0)
            throw std::runtime_error("I2C Cannot open port ");
    }
    i2c::~i2c() {
        if (m_file > 0)
            close(m_file);
    }

    ADS1115::Error i2c::begin(const uint8_t address) const { 
        return getError(ioctl(m_file, I2C_SLAVE, address)); 
    }

    ADS1115::Error i2c::write(uint8_t *data, const size_t length) const {
        auto ret = ::write(m_file, data, length);

        if (ret != static_cast<int>(length))
            return getError(ret);
        else
            return ADS1115::Error::NONE;
    }

    ADS1115::Error i2c::read(uint8_t *data, const size_t length) const {
        const auto ret = ::read(m_file, data, length);

        if (ret != static_cast<int>(length))
            return getError(ret);
        else
            return ADS1115::Error::NONE;
    }
} // namespace unix_i2c

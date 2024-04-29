#pragma once
namespace ADS1115
{
enum Error
{
    NONE,
    ERROR,
    BUSY,
    TIMEOUT,
    BAD_ADDRESS,
    IO,
    INVALID_ARG,
};
};

/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "CodalConfig.h"
#include "MbedSPI.h"
#include "ErrorNo.h"
#include "CodalDmesg.h"

namespace codal
{

/**
 * Constructor.
 */
MbedSPI::MbedSPI(Pin &mosi, Pin &miso, Pin &sclk)
    : mbed::SPI((PinName)mosi.name, (PinName)miso.name, (PinName)sclk.name), codal::SPI()
{
    setFrequency(1000000);
    setMode(0, 8);
}

/** Set the frequency of the SPI interface
 *
 * @param frequency The bus frequency in hertz
 */
int MbedSPI::setFrequency(uint32_t frequency)
{
    mbed::SPI::frequency(frequency);
    return DEVICE_OK;
}

/** Set the mode of the SPI interface
 *
 * @param mode Clock polarity and phase mode (0 - 3)
 * @param bits Number of bits per SPI frame (4 - 16)
 *
 * @code
 * mode | POL PHA
 * -----+--------
 *   0  |  0   0
 *   1  |  0   1
 *   2  |  1   0
 *   3  |  1   1
 * @endcode
 */
int MbedSPI::setMode(int mode, int bits)
{
    mbed::SPI::format(bits, mode);
    return DEVICE_OK;
}

/**
 * Writes the given byte to the SPI bus.
 *
 * The CPU will busy wait until the transmission is complete.
 *
 * @param data The data to write.
 * @return Response from the SPI slave or DEVICE_SPI_ERROR if the the write request failed.
 */
int MbedSPI::write(int data)
{
    int ret = mbed::SPI::write(data);
    return (ret >= 0) ? ret : DEVICE_SPI_ERROR;
}

typedef void (*PVoidIntCallback)(void *, int);

int MbedSPI::xfer(uint8_t const *p_tx_buffer, uint16_t tx_length, uint8_t *p_rx_buffer,
                  uint16_t rx_length, PVoidCallback doneHandler, void *arg)
{
    event_callback_t tmp((PVoidIntCallback)doneHandler, arg);
    doneCb = tmp;
    int rc = mbed::SPI::transfer(p_tx_buffer, tx_length, p_rx_buffer, rx_length, doneCb);
    return rc ? DEVICE_SPI_ERROR : DEVICE_OK;
}

/**
 * Writes a given command to SPI bus, and afterwards reads the response. Finally, calls doneHandler
 * (possibly in IRQ context).
 *
 * Note that bytes recieved while sending command are ignored.
 */
int MbedSPI::startTransfer(const uint8_t *command, uint32_t commandSize, uint8_t *response,
                           uint32_t responseSize, void (*doneHandler)(void *), void *arg)
{
    if (doneHandler == NULL)
        return DEVICE_INVALID_PARAMETER;

    if (commandSize && responseSize)
    {
        // both command and response, fallback to slow mode
        return codal::SPI::startTransfer(command, commandSize, response, responseSize, doneHandler,
                                         arg);
    }
    else if (commandSize)
    {
        return xfer(command, commandSize, NULL, 0, doneHandler, arg);
    }
    else if (responseSize)
    {
        return xfer(NULL, 0, response, responseSize, doneHandler, arg);
    }
    else
    {
        return DEVICE_INVALID_PARAMETER;
    }
}
}


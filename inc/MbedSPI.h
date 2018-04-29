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

#ifndef CODAL_MBED_SPI_H
#define CODAL_MBED_SPI_H

#include "mbed.h"
#include "CodalConfig.h"
#include "SPI.h"
#include "codal-core/inc/driver-models/SPI.h"
#include "Pin.h"

namespace codal
{

/**
 * Class definition for SPI service, derived from ARM mbed.
 */
class MbedSPI : protected mbed::SPI, public codal::SPI
{
public:
    /**
     * Initialize SPI instance with given pins.
     *
     * Default setup is 1 MHz, 8 bit, mode 0.
     */
    MbedSPI(codal::Pin &mosi, codal::Pin &miso, codal::Pin &sclk);

    /** Set the frequency of the SPI interface
     *
     * @param frequency The bus frequency in hertz
     */
    virtual int setFrequency(uint32_t frequency);

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
    virtual int setMode(int mode, int bits = 8);

    /**
     * Writes the given byte to the SPI bus.
     *
     * The CPU will busy wait until the transmission is complete.
     *
     * @param data The data to write.
     * @return Response from the SPI slave or DEVICE_SPI_ERROR if the the write request failed.
     */
    virtual int write(int data);
};
}

#endif

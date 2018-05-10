/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

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
#ifndef CODAL_MBED_I2C_H
#define CODAL_MBED_I2C_H

#include "mbed.h"
#include "Pin.h"
#include "CodalConfig.h"
#include "codal-core/inc/driver-models/I2C.h"

namespace mb = ::mbed;

namespace codal
{
    namespace _mbed
    {
        /**
          * Class definition for I2C service, derived from ARM mbed.
          */
        class I2C : public codal::I2C, private mb::I2C
        {
            public:

            /**
              * Constructor.
              */
            I2C(codal::Pin& sda, codal::Pin& scl);

            /** Set the frequency of the I2C interface
              *
              * @param frequency The bus frequency in hertz
              */
            int setFrequency(uint32_t frequency);

              /**
              * Issues a standard, 2 byte I2C command write to the accelerometer.
              *
              * Blocks the calling thread until complete.
              *
              * @param reg The address of the register to write to.
              *
              * @param value The value to write.
              *
              * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the write request failed.
              */

            int write(uint8_t data);

            /**
              * Issues a single-byte read command.
              *
              * Blocks the calling thread until complete.
              *
              * @return the byte on success or DEVICE_I2C_ERROR if the read request failed.
              */
            int read(AcknowledgeType ack = AcknowledgeType::ACK);

              /**
             * Issues a START condition on the I2C bus
             * @return DEVICE_OK on success, or an error code
             */
            int start();

            /**
             * Issues a STOP condition on the I2C bus
             * @return DEVICE_OK on success, or an error code
             */
            int stop();
        };
    }
}

#endif

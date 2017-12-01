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

#include "MbedTimer.h"
#include "CodalCompat.h"
#include "Timer.h"
#include "CodalConfig.h"
#include "codal_target_hal.h"

#include "CodalDmesg.h"
#define MINIMUM_PERIOD  32

namespace codal
{
    namespace _mbed
    {
        void Timer::triggered()
        {
            timeout.attach_us(callback(this, &Timer::triggered), this->period);
            this->trigger();
        }

        Timer::Timer() : codal::Timer()
        {
            this->period = 10000;
            timer.start();
            timeout.attach_us(callback(this, &Timer::triggered), this->period);
        }

        /**
         * request to the physical timer implementation code to provide a trigger callback at the given time.
         * note: it is perfectly legitimate for the implementation to trigger before this time if convenient.
         * @param t Indication that t time units (typically microsends) have elapsed.
         */
        void Timer::triggerIn(CODAL_TIMESTAMP t)
        {
            if (t < MINIMUM_PERIOD)
                t = MINIMUM_PERIOD;

            timeout.detach();
            timeout.attach_us(callback(this, &Timer::triggered), t);
        }
        /**
         * request to the physical timer implementation code to trigger immediately.
         */
        void Timer::syncRequest()
        {
            disableInterrupts();
            int elapsed = timer.read_us();
            timer.reset();
            this->sync(elapsed);
            enableInterrupts();
        }
    }
}

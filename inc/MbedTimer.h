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

#ifndef CODAL_MBED_TIMER_H
#define CODAL_MBED_TIMER_H

#include "codal-core/inc/types/Event.h"
#include "codal-core/inc/driver-models/Timer.h"
#include "mbed.h"

namespace mb=mbed;

namespace codal
{
    namespace _mbed
    {
        class Timer : public codal::Timer
        {
            uint32_t period;

            mb::Timer timer;
            mb::Timeout timeout;

            void triggered();

        public:

            /**
              * Constructor for an instance of Timer1.
              *
              * @param id The id to use for the message bus when transmitting events.
              */
            Timer();

            /**
             * request to the physical timer implementation code to provide a trigger callback at the given time.
             * note: it is perfectly legitimate for the implementation to trigger before this time if convenient.
             * @param t Indication that t time units (typically microsends) have elapsed.
             */
            virtual void triggerIn(CODAL_TIMESTAMP t);

            /**
             * request to the physical timer implementation code to trigger immediately.
             */
            virtual void syncRequest();
        };
    }
}

#endif

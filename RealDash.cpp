/*
 *  RealDash.cpp
 *
 * Class emulates the serial comm of an ELM327 chip - Used to create an OBDII interface
 *
 * Created: 3/23/2017
 *  Author: Collin Kidder
 */

/*
 Copyright (c) 2017 Collin Kidder

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RealDash.h"
#include "config.h"
#include "Logger.h"
#include "utility.h"
#include "esp32_can.h"
#include "can_manager.h"

/*
 * Constructor. Nothing at the moment
 */
RealDash::RealDash() 
{
    mClient = 0;
}

/*
 * Initialization of hardware and parameters
 */
void RealDash::setup() {
    // noop
}

void RealDash::setWiFiClient(WiFiClient *client)
{
    mClient = client;
}

/*
 * Called in the main loop (hopefully) in order to process serial input waiting for us
 * from the wifi module. It should always terminate its answers with 13 so buffer
 * until we get 13 (CR) and then process it.
 * But, for now just echo stuff to our serial port for debugging
 */

void RealDash::loop() {
    if (mClient) {
        int incoming;
        while (mClient->available()) {
            incoming = mClient->read();
            // just read so that this doesn't blow up for now
        }
    }
}

void RealDash::sendTxBuffer()
{
    if (mClient)
    {
        size_t wifiLength = txBuffer.numAvailableBytes();
        uint8_t* buff = txBuffer.getBufferedBytes();
        if (mClient->connected())
        {
            mClient->write(buff, wifiLength);
        }
    }
    txBuffer.clearBufferedBytes();
}

void RealDash::processCANReply(CAN_FRAME &frame)
{
    // whitelist
    if (frame.id == 289
        || frame.id == 253
        || frame.id == 167
        || frame.id == 168) {

        // send realdash can frame
        txBuffer.sendFrameToBufferRealDash(frame);
        sendTxBuffer();

    }
}

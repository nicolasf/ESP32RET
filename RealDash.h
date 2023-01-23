/*
 *  RealDash.h
 *
 * Class forwards data using RealDash CAN Protocol.
 *
 * Created: 1/23/2023
 *  Author: Nicolas Frenay
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


#ifndef REALDASH_H_
#define REALDASH_H_

#include <Arduino.h>
#include <WiFi.h>
#include "commbuffer.h"

class CAN_FRAME;

class RealDash {
public:
    RealDash();
    void setup(); //initialization on start up
    void loop();
    void setWiFiClient(WiFiClient *client);
    void processCANReply(CAN_FRAME &frame);

private:
    WiFiClient *mClient;
    CommBuffer txBuffer;

    void sendTxBuffer();
};

#endif

/*
 * File:   command.h
 *
 * Copyright (C) 2014 pic32mcu@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifndef COMMAND_H
#define	COMMAND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "USB/usb.h"
#include "HardwareProfile.h"

#ifndef dim
#define dim(x)  (sizeof(x) / sizeof(x[0]))
#endif

    //Definitions of the various application commnands that can be sent
    typedef enum _PIC32_KIT_COMMANDS {
        COMMAND_UPDATE_LED = 0x01,
        COMMAND_UPDATE_BUTTON = 0x02,
        COMMAND_SELECT_CITY = 0x03
    } PIC32_KIT_COMMANDS;

    typedef enum _SELECT_CITY_ARG {
        SELECT_CITY_PREV = 0,
        SELECT_CITY_NEXT = 1
    } SELECT_CITY_ARG;

    //Creation of the data packet that is going to be sent.  In this example
    //  there is just a command code and a two bytes data.
    typedef struct __attribute__((packed)) {
        BYTE command;
        BYTE data0;
        BYTE data1;
    }
    PIC32KIT_APP_PACKET;

    extern BOOL isReadyToSendCommand(void *device_handle);
    extern void beginSendCommand(void);
    extern BOOL sendCommand(BYTE cmd, BYTE data0, BYTE data1);
    extern void endSendCommand(void *device_handle);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMAND_H */


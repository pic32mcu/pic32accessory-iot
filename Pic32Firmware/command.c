/*
 * File:   command.c
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
#include "command.h"

static int _outgoingPacketIndex = 0;
static PIC32KIT_APP_PACKET _outgoingPackets[16];

static BOOL _readyToWrite = TRUE;

BOOL isReadyToSendCommand(void *device_handle)
{
    DWORD size = 0;
    BYTE errorCode;
    if(_readyToWrite == FALSE) {
        if (AndroidAppIsWriteComplete(device_handle, &errorCode, &size) == TRUE) {
            _readyToWrite = TRUE;
            if (errorCode != USB_SUCCESS) {
                DEBUG_PrintString("Error trying to complete write");
            }
        }
    }
    return _readyToWrite;
}

void beginSendCommand(void) {
    _outgoingPacketIndex = 0;
}

BOOL sendCommand(BYTE cmd, BYTE data0, BYTE data1) {
    if( _outgoingPacketIndex < (dim(_outgoingPackets)-1) ) {
        _outgoingPackets[_outgoingPacketIndex].command = cmd;
        _outgoingPackets[_outgoingPacketIndex].data0 = data0;
        _outgoingPackets[_outgoingPacketIndex].data1 = data1;
        _outgoingPacketIndex++;
    } else {
        return FALSE;
    }
}

void endSendCommand(void *device_handle) {
    BYTE errorCode;
    if (_outgoingPacketIndex > 0) {
        errorCode = AndroidAppWrite(device_handle, (BYTE*) & _outgoingPackets[0], _outgoingPacketIndex * sizeof (PIC32KIT_APP_PACKET));
        if (errorCode != USB_SUCCESS) {
            DEBUG_PrintString("Error trying to send button update");
        }
        _readyToWrite = FALSE;
    }
}
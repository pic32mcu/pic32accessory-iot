/*
 * File:   led.c
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
#include "led.h"

static LED _led[3];

static int getLedIndex(BYTE id) {
    int i;
    for(i=0; i<dim(_led); i++) {
        if(_led[i].id == id)
            return i;
    }
    return -1;
}

void initLed(void)
{
    int i;
    InitAllLEDs();
    for(i=0; i<dim(_led); i++) {
        _led[i].id = (BYTE)(i+1);
        _led[i].state = LED_STATE_OFF;
        _led[i].changed = FALSE;
        _led[i].emulate_state = LED_STATE_OFF;
        _led[i].emulate_changed = FALSE;
    }
}

static BOOL assignLedState(BOOL emulate, BYTE id, LED_STATE state)
{
    int idx;

    if(state != LED_STATE_ON && state != LED_STATE_OFF)
        return FALSE;

    idx = getLedIndex(id);
    if(idx < 0)
        return FALSE;

    if (emulate == FALSE) {
        if (_led[idx].state != state) {
            _led[idx].state = state;
            _led[idx].changed = TRUE;
        }
    } else {
        if (_led[idx].emulate_state != state) {
            _led[idx].emulate_state = state;
            _led[idx].emulate_changed = TRUE;
        }
    }

    if(_led[idx].changed || _led[idx].emulate_changed) {
        switch(idx) {
            case 0:
                if(state==LED_STATE_OFF) { LED0_Off(); } else { LED0_On(); }
                break;
            case 1:
                if(state==LED_STATE_OFF) { LED1_Off(); } else { LED1_On(); }
                break;
            case 2:
                if(state==LED_STATE_OFF) { LED2_Off(); } else { LED2_On(); }
                break;
            default:
                return FALSE;
        }
    }
    return TRUE;
}

BOOL setLedState(BYTE id, LED_STATE state)
{
    return assignLedState(FALSE, id, state);
}

BOOL setLedEmulateState(BYTE id, LED_STATE state)
{
    return assignLedState(TRUE, id, state);
}

static LED_STATE retLedState(BOOL emulate, BYTE id)
{
    int idx = getLedIndex(id);
    if(idx < 0)
        return LED_STATE_UNDEFINE;
    return (emulate==FALSE)? _led[idx].state : _led[idx].emulate_state;
}

LED_STATE getLedState(BYTE id)
{
    return retLedState(FALSE, id);
}

LED_STATE getLedEmulateState(BYTE id)
{
    return retLedState(TRUE, id);
}

static BYTE findStateChangedLedID(BOOL emulate)
{
    int i;
    for(i=0; i<dim(_led); i++) {
        if (emulate == FALSE) {
            if (_led[i].changed) {
                _led[i].changed = FALSE;
                return _led[i].id;
            }
        } else {
            if (_led[i].emulate_changed) {
                _led[i].emulate_changed = FALSE;
                return _led[i].id;
            }
        }
    }
    return LED_UNDEFINE_ID;
}

// return ID of the led whose state is changed
// "changed" property will be cleared once ID is returned
BYTE getStateChangedLedID(void)
{
    return findStateChangedLedID(FALSE);
}

// return ID of the led whose emulate_state is changed
// "emulate_state" property will be cleared once ID is returned
BYTE getEmulateStateChangedLedID(void)
{
    return findStateChangedLedID(TRUE);
}

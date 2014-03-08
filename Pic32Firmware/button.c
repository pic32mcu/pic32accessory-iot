/*
 * File:   button.c
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
#include "button.h"

static BUTTON _button[3];

static int getButtonIndex(BYTE id) {
    int i;
    for(i=0; i<dim(_button); i++) {
        if(_button[i].id == id)
            return i;
    }
    return -1;
}

void initButton(void)
{
    int i;
    for(i=0; i<dim(_button); i++) {
        _button[i].id = (BYTE)(i+1);
        _button[i].state = BUTTON_STATE_UP;
        _button[i].changed = FALSE;
        _button[i].emulate_state = BUTTON_STATE_UP;
        _button[i].emulate_changed = FALSE;
    }
}

void pollButtonState(void)
{
    InitAllSwitches();
    setButtonState(1, Switch1Pressed()? BUTTON_STATE_DOWN : BUTTON_STATE_UP);
    setButtonState(2, Switch2Pressed()? BUTTON_STATE_DOWN : BUTTON_STATE_UP);
    setButtonState(3, Switch3Pressed()? BUTTON_STATE_DOWN : BUTTON_STATE_UP);
}

static BYTE findStateChangedButtonID(BOOL emulate)
{
    int i;
    for(i=0; i<dim(_button); i++) {
        if (emulate == FALSE) {
            if (_button[i].changed) {
                _button[i].changed = FALSE;
                return _button[i].id;
            }
        } else {
            if (_button[i].emulate_changed) {
                _button[i].emulate_changed = FALSE;
                return _button[i].id;
            }
        }
    }
    return BUTTON_UNDEFINE_ID;
}

// return ID of the button whose it state is changed
// "changed" property will be cleared once ID is returned
BYTE getStateChangedButtonID(void)
{
    return findStateChangedButtonID(FALSE);
}

// return ID of the button whose emulate_state is changed
// "emulate_state" property will be cleared once ID is returned
BYTE getEmulateStateChangedButtonID(void)
{
    return findStateChangedButtonID(TRUE);
}

static BUTTON_STATE retButtonState(BOOL emulate, BYTE id)
{
    int idx = getButtonIndex(id);
    if(idx < 0)
        return BUTTON_STATE_UNDEFINE;
    return (emulate==FALSE)? _button[idx].state : _button[idx].emulate_state;
}

BUTTON_STATE getButtonState(BYTE id)
{
    return retButtonState(FALSE, id);
}

BUTTON_STATE getButtonEmulateState(BYTE id)
{
    return retButtonState(TRUE, id);
}

static BOOL assignButtonState(BOOL emulate, BYTE id, BUTTON_STATE state)
{
    int idx;

    if(state != BUTTON_STATE_DOWN && state != BUTTON_STATE_UP)
        return FALSE;

    idx = getButtonIndex(id);
    if(idx < 0)
        return FALSE;

    if (emulate == FALSE) {
        if (_button[idx].state != state) {
            _button[idx].state = state;
            _button[idx].changed = TRUE;
        }
    } else {
        if (_button[idx].emulate_state != state) {
            _button[idx].emulate_state = state;
            _button[idx].emulate_changed = TRUE;
        }
    }
    return TRUE;
}

BOOL setButtonState(BYTE id, BUTTON_STATE state)
{
    return assignButtonState(FALSE, id, state);
}

BOOL setButtonEmulateState(BYTE id, BUTTON_STATE state)
{
    return assignButtonState(TRUE, id, state);
}
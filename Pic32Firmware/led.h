/* 
 * File:   led.h
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

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "HardwareProfile.h"

#ifndef dim
#define dim(x)  (sizeof(x) / sizeof(x[0]))
#endif

#define LED_UNDEFINE_ID 0xff

typedef enum _LED_STATE
{
    LED_STATE_OFF       = 0x00,
    LED_STATE_ON        = 0x01,
    LED_STATE_UNDEFINE  = 0x02
} LED_STATE;

typedef struct __attribute__((packed))
{
    BYTE id;
    LED_STATE state;
    BOOL changed;
    LED_STATE emulate_state;
    BOOL emulate_changed;
} LED;

extern void initLed(void);
extern BYTE getStateChangedLedID(void);
extern BYTE getEmulateStateChangedLedID(void);
extern LED_STATE getLedState(BYTE id);
extern LED_STATE getLedEmulateState(BYTE id);
extern BOOL setLedState(BYTE id, LED_STATE state);
extern BOOL setLedEmulateState(BYTE id, LED_STATE state);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */


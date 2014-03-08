/* 
 * File:   button.h
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

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "HardwareProfile.h"

#ifndef dim
#define dim(x)  (sizeof(x) / sizeof(x[0]))
#endif

#define BUTTON_UNDEFINE_ID 0xff

typedef enum _BUTTON_STATE
{
    BUTTON_STATE_DOWN       = 0x00,
    BUTTON_STATE_UP         = 0x01,
    BUTTON_STATE_UNDEFINE   = 0x02
} BUTTON_STATE;

typedef struct __attribute__((packed))
{
    BYTE id;
    BUTTON_STATE state;
    BOOL changed;
    BUTTON_STATE emulate_state;
    BOOL emulate_changed;
} BUTTON;

extern void initButton(void);
extern void pollButtonState(void);
extern BYTE getStateChangedButtonID(void);
extern BYTE getEmulateStateChangedButtonID(void);
extern BUTTON_STATE getButtonState(BYTE id);
extern BUTTON_STATE getButtonEmulateState(BYTE id);
extern BOOL setButtonState(BYTE id, BUTTON_STATE state);
extern BOOL setButtonEmulateState(BYTE id, BUTTON_STATE state);

#ifdef	__cplusplus
}
#endif

#endif	/* SW_H */

/*
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
package net.pic32mcu.accessory;

public class Constant {
	
	// command opcode
	public static final byte COMMAND_MIN = 1;
	public static final byte COMMAND_UPDATE_LED = 1;
	public static final byte COMMAND_UPDATE_BUTTON = 2;
	public static final byte COMMAND_SELECT_CITY = 3;
	public static final byte COMMAND_MAX = 3;

	// byte value and string for led
	public static final byte LED_ON_VALUE = 1;
	public static final byte LED_OFF_VALUE = 0;
	public static final String LED_ON_STRING = "on";
	public static final String LED_OFF_STRING = "off";

	// byte value and string for button
	public static final byte BUTTON_DOWN_VALUE = 0;
	public static final byte BUTTON_UP_VALUE = 1;
	public static final String BUTTON_UP_STRING = "up";
	public static final String BUTTON_DOWN_STRING = "down";

	// byte value and string for select next/prev city
	public static final byte PICK_NEXT_CITY_VALUE = 1;
	public static final byte PICK_PREV_CITY_VALUE = 0;
	public static final String PICK_NEXT_CITY_STRING = "city-next";
	public static final String PICK_PREV_CITY_STRING = "city-prev";

}

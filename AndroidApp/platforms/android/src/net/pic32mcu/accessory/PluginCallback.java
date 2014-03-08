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

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;

public class PluginCallback implements Runnable {
	CallbackContext callbackContext;
	String strSuccess;
	String strError;

	public PluginCallback(CallbackContext callbackContext, String success,
			String error) {
		this.callbackContext = callbackContext;
		this.strSuccess = success;
		this.strError = error;
	}

	/*
	 * if success != null, invoke callback.success(success); else if error !=
	 * null, invoke callback.error(error); else invoke callback.success()
	 */
	public static void invoke(CordovaInterface cordova,
			CallbackContext callbackContext, String success, String error) {
		if (callbackContext != null) {
			cordova.getActivity().runOnUiThread(
					new PluginCallback(callbackContext, success, error));
		}
	}

	@Override
	public void run() {
		if (strSuccess != null) {
			callbackContext.success(strSuccess);
		} else if (strError != null) {
			this.callbackContext.error(strError);
		} else {
			callbackContext.success();
		}
	}

}

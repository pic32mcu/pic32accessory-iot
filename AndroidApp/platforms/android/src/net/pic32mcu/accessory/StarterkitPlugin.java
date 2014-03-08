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
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;

import android.util.Log;

public class StarterkitPlugin extends CordovaPlugin {

    private AccessoryManager mAccessoryManager;

    private static final String TAG = "StarterkitPlugin";

    @Override
    public boolean execute(String action, JSONArray args, 
            CallbackContext callbackContext) throws JSONException {

        if("start".equals(action)) {
            // run on Thread without UI
        	return start(callbackContext);
            
        } else if("stop".equals(action)) {
        	// run on Thread without UI
        	stop(callbackContext);
            return true;

		} else if ("userActionLed".equals(action)) {
			userActionLed(callbackContext, args);
        	
        } else if("userActionButton".equals(action)) {
        	userActionButton(callbackContext, args);
        	
        } else if("echo".equals(action)) {
            /* run on WebCore thread */
            String message = args.getString(0);
            this.echo(message, callbackContext);

            /* run on UI Thread
             final long duration = args.getLong(0);
             cordova.getActivity().runOnUiThread(new Runnable() {
             public void run() {
             //...
             callbackContext.success(); // Thread-safe.
             }
             });
             */
            /* run on Thread without UI
             final long duration = args.getLong(0);
             cordova.getThreadPool().execute(new Runnable() {
             public void run() {
             //...
             callbackContext.success(); // Thread-safe.
             }
             });
             */
            ///*
            cordova.getActivity().runOnUiThread(new Runnable() {
                public void run() {
                    Log.d(TAG, "runOnUiThread");
                    webView.loadUrl("javascript:try{cordova.fireDocumentEvent('starterkit', {'json':{'text1':'hello','text2':'hey'},'msg':' hi'});}catch(e){console.log('exception firing message event from native');};");
                    //webView.loadUrl("javascript:try{cordova.fireDocumentEvent('message', {'detail':'hello','msg':' hi'});cordova.fireWindowEvent('message', 'hello');}catch(e){console.log('exception firing message event from native');};");
                }
            });
            //*/

            return true;
        }
        return false;
    }

    @Override
    public void onPause(boolean multitasking) {
        super.onPause(multitasking);
    }
    
    @Override
    public void onResume(boolean multitasking) {
        super.onResume(multitasking);
    }
    
    @Override
	public void onDestroy() {
    	stop(null);
		super.onDestroy();
	}

	@Override
    public void onReset() {
        /*
        Plugins with long-running requests, background activity such as media playback, 
        listeners, or internal state should implement the onReset() method as well. 
        It executes when the WebView navigates to a new page or refreshes, which 
        reloads the JavaScript.
        */
        super.onReset();
    }
	
	private boolean start(CallbackContext callbackContext) {
		Log.d(TAG, "start");

		if(mAccessoryManager == null) {
			AccessoryManager mgr = new AccessoryManager(cordova, webView, callbackContext);
			if(mgr.connect()) {
				mAccessoryManager = mgr;
				PluginCallback.invoke(cordova, callbackContext, null, null);
			} else {
				PluginCallback.invoke(cordova, callbackContext, null, "Fail to connect accessory!");
			}
			
		} else {
			PluginCallback.invoke(cordova, callbackContext, null, "StarterkitPlugin already started!");
		}

		return true;
	}
	
	private void stop(CallbackContext callbackContext) {
		Log.d(TAG, "stop");
		
    	if(mAccessoryManager != null) {
    		mAccessoryManager.disconnect();
    		mAccessoryManager = null;
    	}
    	
    	// invoke callback.success()
    	PluginCallback.invoke(cordova, callbackContext, null, null);
	}
	
	private void userActionLed(CallbackContext callbackContext, JSONArray args)
			throws JSONException {
		final int led = args.getInt(0);
		final String status = args.getString(1);
		Log.d(TAG, "userActionLed: led = " + String.valueOf(led)
				+ ", status = " + status);

		mAccessoryManager.sendCommand(Constant.COMMAND_UPDATE_LED, (byte) led,
				Constant.LED_ON_STRING.equals(status) ? Constant.LED_ON_VALUE
						: Constant.LED_OFF_VALUE);

		// invoke callback.success()
		PluginCallback.invoke(cordova, callbackContext, null, null);
	}
	
	private void userActionButton(CallbackContext callbackContext,
			JSONArray args) throws JSONException {
		final int button = args.getInt(0);
		final String status = args.getString(1);

		Log.d(TAG, "userActionButton: button = " + String.valueOf(button)
				+ ", status = " + status);

		mAccessoryManager
				.sendCommand(
						Constant.COMMAND_UPDATE_BUTTON,
						(byte) button,
						Constant.BUTTON_UP_STRING.equals(status) ? Constant.BUTTON_UP_VALUE
								: Constant.BUTTON_DOWN_VALUE);

		// invoke callback.success()
		PluginCallback.invoke(cordova, callbackContext, null, null);
	}

    private void echo(String message, CallbackContext callbackContext) {
        if (message != null && message.length() > 0) {
            callbackContext.success(message);
            Log.d(TAG, "callbackContext.success");
        } else {
            callbackContext.error("Expected one non-empty string argument.");
            Log.d(TAG, "callbackContext.error");
        }
    }
}

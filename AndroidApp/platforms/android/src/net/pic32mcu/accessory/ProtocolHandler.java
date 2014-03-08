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

import java.io.IOException;
import java.io.InputStream;

import org.apache.cordova.CordovaWebView;

import android.app.Activity;
import android.util.Log;

import com.google.android.apps.adk2.Utilities;

public class ProtocolHandler {
	
	private static final String TAG = "ProtocolHandler";
	
	private Activity activity;
	private CordovaWebView webView;
	private InputStream inputStream;

	public ProtocolHandler(Activity activity, CordovaWebView webView, InputStream inputStream) {
		this.activity = activity;
		this.webView = webView;
		this.inputStream = inputStream;
	}

	int readByte() throws IOException {
		int retVal = inputStream.read();
		if (retVal == -1) {
			throw new RuntimeException("End of stream reached.");
		}
		return retVal;
	}

	int readInt16() throws IOException {
		int low = readByte();
		int high = readByte();
		//Log.i(TAG, "readInt16 low=" + low + " high=" + high);
		return low | (high << 8);
	}

	byte[] readBuffer(int bufferSize) throws IOException {
		byte readBuffer[] = new byte[bufferSize];
		int index = 0;
		int bytesToRead = bufferSize;
		while (bytesToRead > 0) {
			int amountRead = inputStream.read(readBuffer, index,
					bytesToRead);
			if (amountRead == -1) {
				throw new RuntimeException("End of stream reached.");
			}
			bytesToRead -= amountRead;
			index += amountRead;
		}
		return readBuffer;
	}

	public void process() {
		inputStream.mark(0);
		try {
			while (inputStream.available() > 0) {
				int opCode = readByte();
				Log.i(TAG, "opCode = " + opCode);
				if (isValidOpCode(opCode)) {
					byte[] replyBuffer = readBuffer(2);
					//Log.i(TAG, "replyBuffer: " + Utilities.dumpBytes(replyBuffer, replyBuffer.length));
					processReply(opCode, replyBuffer);
					inputStream.mark(0);
				}
			}
			inputStream.reset();
		} catch (IOException e) {
			Log.d(TAG, "ProtocolHandler error " + e.toString());
		}
	}
	
	boolean isValidOpCode(int opCodeWithReplyBitSet) {
		int opCode = opCodeWithReplyBitSet & 0x7f;
		return ((opCode >= Constant.COMMAND_MIN) && (opCode <= Constant.COMMAND_MAX));
	}
	
	private void processReply(int opCode, byte[] data) {
		switch(opCode) {
		case Constant.COMMAND_UPDATE_LED:
			JavascriptEvent.fireLedStatus(activity, webView, Utilities
					.unsignedByte(data[0]),
					data[1] == Constant.LED_OFF_VALUE ? Constant.LED_OFF_STRING
							: Constant.LED_ON_STRING);
			break;
			
		case Constant.COMMAND_UPDATE_BUTTON:
			JavascriptEvent
					.fireSwStatus(
							activity,
							webView,
							Utilities.unsignedByte(data[0]),
							data[1] == Constant.BUTTON_UP_VALUE ? Constant.BUTTON_UP_STRING
									: Constant.BUTTON_DOWN_STRING);
			break;
			
		case Constant.COMMAND_SELECT_CITY:
			JavascriptEvent
					.fireSimpleEvent(
							activity,
							webView,
							data[0] == Constant.PICK_NEXT_CITY_VALUE ? Constant.PICK_NEXT_CITY_STRING
									: Constant.PICK_PREV_CITY_STRING);
			break;
		}
	}
}

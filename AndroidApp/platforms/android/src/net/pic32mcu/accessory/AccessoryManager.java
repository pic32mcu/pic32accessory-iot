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

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.concurrent.Future;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaWebView;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.google.android.apps.adk2.BTConnection;
import com.google.android.apps.adk2.Connection;
import com.google.android.apps.adk2.UsbConnection;
import com.google.android.apps.adk2.Utilities;

public class AccessoryManager implements Runnable {

	private static final String TAG = "AccessoryManager";
	private static final boolean gLogPackets = false;

	private boolean taskIsDone = false;
	private Future<?> mThread = null;
	
	private CordovaInterface cordova;
	private CordovaWebView webView;

	private Connection mConnection = null;

	public AccessoryManager(CordovaInterface cordova, CordovaWebView webView,
			CallbackContext callbackContext) {
		this.cordova = cordova;
		this.webView = webView;
	}

	public boolean connect() {
		// bail out if we're already connected
		if (mConnection != null)
			return true;

		Activity activity = cordova.getActivity();

		if (activity.getIntent().hasExtra(
				BTDeviceListActivity.EXTRA_DEVICE_ADDRESS)) {
			String address = activity.getIntent().getStringExtra(
					BTDeviceListActivity.EXTRA_DEVICE_ADDRESS);
			Log.d(TAG, "BT connection: " + address);
			mConnection = new BTConnection(address);
			performPostConnectionTasks();
		} else {
			mConnection = UsbConnection.create(activity);
			if(mConnection != null) {
				Log.d(TAG, "UsbConnection done");
				performPostConnectionTasks();
			} else {
				Log.e(TAG, "Either UsbManager permission error or Accessory null error!");
				return false;
			}
		}

		return true;
	}

	public void disconnect() {
		setTaskComplete();
		if(mThread != null) {
			mThread.cancel(true);
			mThread = null;
		}
		if (mConnection != null) {
			try {
				mConnection.close();
			} catch (IOException e) {
				Log.d(TAG, e.toString());
			} finally {
				mConnection = null;
			}
		}
	}
	
	private void performPostConnectionTasks() {
		clrTaskComplete();
		mThread = cordova.getThreadPool().submit(this);
	}

	private synchronized boolean isTaskComplete() {
		return taskIsDone;
	}

	private synchronized void setTaskComplete() {
		taskIsDone = true;
	}
	
	private synchronized void clrTaskComplete() {
		taskIsDone = false;
	}
	
	@Override
	public void run() {
		int ret = 0;
		byte[] buffer = new byte[16384];
		int bufferUsed = 0;
		
		while ( !isTaskComplete() && (ret >= 0) ) {
			try {
				ret = mConnection.getInputStream().read(buffer, bufferUsed,
						buffer.length - bufferUsed);
				bufferUsed += ret;
				int remainder = process(buffer, bufferUsed);
				if (remainder > 0) {
					System.arraycopy(buffer, remainder, buffer, 0, bufferUsed
							- remainder);
					bufferUsed = remainder;
				} else {
					bufferUsed = 0;
				}
			} catch (IOException e) {
				Log.d(TAG, e.toString());
				break;
			}
		}
		Activity activity = cordova.getActivity();
		Intent connectIntent = new Intent(activity, ConnectActivity.class);
		connectIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
		activity.startActivity(connectIntent);
		activity.finish();
	}
	
	public int process(byte[] buffer, int bufferUsed) {
		if (gLogPackets) {
			Log.i(TAG,
					"read " + bufferUsed + " bytes: "
							+ Utilities.dumpBytes(buffer, bufferUsed));
		}
		ByteArrayInputStream inputStream = new ByteArrayInputStream(buffer, 0,
				bufferUsed);
		ProtocolHandler ph = new ProtocolHandler(cordova.getActivity(), webView, inputStream);
		ph.process();
		return inputStream.available();
	}

	
	public byte[] sendCommand(int command, byte[] payload, byte[] buffer) {
		int bufferLength = payload.length + 1;
		if (buffer == null || buffer.length < bufferLength) {
			Log.i(TAG, "allocating new command buffer of length "
					+ bufferLength);
			buffer = new byte[bufferLength];
		}

		buffer[0] = (byte) command;
		if (payload.length > 0) {
			System.arraycopy(payload, 0, buffer, 1, payload.length);
		}
		if (mConnection != null) {
			try {
				if (gLogPackets) {
					Log.i(TAG,
							"sendCommand: "
									+ Utilities
											.dumpBytes(buffer, buffer.length));
				}
				mConnection.getOutputStream().write(buffer);
			} catch (IOException e) {
				Log.e(TAG, "accessory write failed", e);
			}
		}
		return buffer;
	}
	
	public void sendCommand(int command, byte data0, byte data1) {
		byte[] payload = new byte[2];
		payload[0] = data0;
		payload[1] = data1;
		sendCommand(command, payload, null);
	}
}

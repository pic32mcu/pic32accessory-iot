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

import org.apache.cordova.CordovaWebView;

import android.app.Activity;

public class JavascriptEvent implements Runnable {

	//private static final String TAG = "JavascriptEvent";

	private final CordovaWebView webView;
	private final String js;

	private static final String JAVASCRIPT_PREFIX = "javascript:try{cordova.fireDocumentEvent('starterkit', {'json':";
	private static final String JAVASCRIPT_SUFFIX = "});}catch(e){console.log('exception firing message event from native');};";

	public JavascriptEvent(CordovaWebView webView, String js) {
		this.webView = webView;
		this.js = js;
	}

	public static void fireLedStatus(Activity activity, CordovaWebView webView,
			int led, String status) {
		StringBuilder sb = new StringBuilder(JAVASCRIPT_PREFIX)
				.append("{'event':'led-status','id':'")
				.append(String.valueOf(led)).append("','status':'")
				.append(status).append("'}").append(JAVASCRIPT_SUFFIX);

		activity.runOnUiThread(new JavascriptEvent(webView, sb.toString()));
	}

	public static void fireSwStatus(Activity activity, CordovaWebView webView,
			int sw, String status) {
		StringBuilder sb = new StringBuilder(JAVASCRIPT_PREFIX)
				.append("{'event':'button-status','id':'")
				.append(String.valueOf(sw)).append("','status':'")
				.append(status).append("'}").append(JAVASCRIPT_SUFFIX);

		activity.runOnUiThread(new JavascriptEvent(webView, sb.toString()));
	}

	public static void fireSimpleEvent(Activity activity,
			CordovaWebView webView, String ev) {
		StringBuilder sb = new StringBuilder(JAVASCRIPT_PREFIX)
				.append("{'event':'").append(ev).append("'}")
				.append(JAVASCRIPT_SUFFIX);

		activity.runOnUiThread(new JavascriptEvent(webView, sb.toString()));
	}

	@Override
	public void run() {
		if (webView != null && js != null) {
			// Log.d(TAG, "run: js = " + js);
			webView.loadUrl(js);
		}
	}
}

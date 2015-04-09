package com.scopely.plugin_s;

import android.content.Context;
import android.util.Log;

public class PluginS {
	private static final String TAG = PluginS.class.getCanonicalName();
	public void voidValuedMethod() {
		Log.d(TAG, "in void valued method");
	}

	private static Context context = null;
	//todo: handlers for running things on UI and GL threads

	public static void initialize(Context context) {
		PluginS.context = context;
		Log.d(TAG, "initialize WOOT!");
	}

	//todo: activity lifecycle callbacks

	public static Object createPlugin(String pluginClassName) {
		Log.d(TAG, "creating plugin with class name " + pluginClassName);
		Class<?> cls;
		String nameWithDots = pluginClassName.replace('/', '.');
		try {
			cls = Class.forName(nameWithDots);
		} catch (ClassNotFoundException e) {
			Log.e(TAG, "Class " + nameWithDots + " not found.");
			e.printStackTrace();
			return null;
		}

		if (context == null) {
			Log.e(TAG, "Trying to initialize plugin without first initializing plugin system.");
			return null;
		}

		try {
			Object result = cls.getDeclaredConstructor(Context.class).newInstance(context);
			return result;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

}

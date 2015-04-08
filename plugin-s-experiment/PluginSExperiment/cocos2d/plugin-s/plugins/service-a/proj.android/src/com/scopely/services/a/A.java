package com.scopely.services.a;

import android.content.Context;
import android.util.Log;

public class A {
	private static final String TAG = A.class.getCanonicalName();

	private Context context;

	public A(Context context) {
		Log.d(TAG, "in constructor with context.");
		this.context = context;
	}

	public void voidValuedMethod() {
		Log.d(TAG, "in void valued method.");
	}
	public int intValuedMethod() {
		Log.d(TAG, "in int valued method.");
		return 420;
	}
	public String stringValuedMethod() {
		Log.d(TAG, "in string valued method.");
		return "this is a string result";
	}
}

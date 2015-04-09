/*
 * todo: legal mumbo jumbo
 */

#include "PluginUtils.h"
#include "JniMacros.h"
#include "PluginJniHelper.h"

namespace scopely
{
	namespace plugin_s
	{
		bool PluginUtils::initializePluginSystem(android_app *androidApp)
		{
			JNIEnv *jniEnv = PluginJniHelper::getJNIEnv();
			if (!jniEnv)
			{
				LOGD("could not get JNI Environment.");
				return false;
			}
			jclass aJclass;
			jmethodID aJmethodID;
			if (!PluginJniHelper::getStaticMethodInfo(jniEnv, &aJclass, &aJmethodID, "com/scopely/plugin_s/PluginS", "initialize", "(Landroid/content/context;)V"))
			{
				LOGD("could not get method ID for static method com.scopely.plugin_s.PluginS#initialize(android.content.Context).");
				return false;
			}

			jniEnv->CallStaticVoidMethod(aJclass, aJmethodID, androidApp->activity->clazz);
			jniEnv->DeleteLocalRef(aJclass);

			return true;
		}
	}
}
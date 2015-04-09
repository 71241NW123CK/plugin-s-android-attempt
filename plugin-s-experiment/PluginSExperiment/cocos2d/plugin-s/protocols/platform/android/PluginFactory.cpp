/*
 * todo: legal mumbo jumbo
 */

#include <jni.h>
#include <cstring>
#include "PluginFactory.h"
#include "JniMacros.h"
#include "PluginInstanceMap.h"
#include "PluginJniHelper.h"
#include "APlugin.h"
#include "BPlugin.h"

namespace scopely
{
	namespace plugin_s
	{
		Plugin *PluginFactory::createPlugin(std::string name, std::string objectiveCComponentClassName, std::string androidJavaComponentClassName)
		{
			if (name == "")
			{
				LOGD("Trying to create a plugin without a name.");
				return NULL;
			}
			JNIEnv *jniEnv = PluginJniHelper::getJNIEnv();
			if (!jniEnv)
			{
				LOGD("Failed to get JNI environment.");
				return NULL;
			}
			jclass pluginSJclass;
			jmethodID createPluginJmethodID;
			if (!PluginJniHelper::getStaticMethodInfo(jniEnv, &pluginSJclass, &createPluginJmethodID, "com/scopely/plugin_s/PluginS", "createPlugin", "(Ljava/lang/String;)Ljava/lang/Object;"))
			{
				LOGD("Failed to get method info for static method com.scopely.plugin_s.PluginS#createPlugin(String)");
				return NULL;
			}
			jstring androidJavaComponentClassNameJstring = jniEnv->NewStringUTF(androidJavaComponentClassName.c_str());
			jobject pluginJobject = jniEnv->CallStaticObjectMethod(pluginSJclass, createPluginJmethodID, androidJavaComponentClassNameJstring);
			jniEnv->DeleteLocalRef(androidJavaComponentClassNameJstring);
			jniEnv->DeleteLocalRef(pluginSJclass);
			Plugin *result;
			if (androidJavaComponentClassName == "com/scopely/services/a/A")
			{
				result = new APlugin();
			}
			else if (androidJavaComponentClassName == "com/scopely/services/b/B")
			{
				result = new BPlugin();
			}
			else
			{
				result = new Plugin();
			}

			PluginInstanceMap::setPluginObject(result, pluginJobject);
			PluginInstanceMap::setPluginJavaClassName(result, androidJavaComponentClassName);

			return result;
		}
	}
}
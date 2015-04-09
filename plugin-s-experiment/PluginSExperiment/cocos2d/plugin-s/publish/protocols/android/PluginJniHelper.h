/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_PluginJniHelper_h
#define Protocol_PluginJniHelper_h

#include <jni.h>
#include <string>

namespace scopely
{
	namespace plugin_s
	{
		class PluginJniHelper
		{
		public:
			static JavaVM *getJavaVM();
			static void setJavaVM(JavaVM *javaVM);
			static JNIEnv *getJNIEnv();
			static bool getStaticMethodInfo(JNIEnv *jniEnv, jclass *pJclass, jmethodID *pJmethodID, const char *className, const char *methodName, const char *jvmMethodSignature);
			static bool getMethodInfo(JNIEnv *jniEnv, jclass *pJclass, jmethodID *pJmethodID, const char *className, const char *methodName, const char *jvmMethodSignature);
			static std::string stringForJstring(jstring aJstring);
			static bool setClassLoaderFromNativeActivity(jobject nativeActivity);
			static jmethodID sharedLoadClassMethodID;
			static jobject sharedClassLoader;
		private:
			static JavaVM *sharedJavaVM;
			static jmethodID getMethodIDWithDefaultClassLoader(JNIEnv *jniEnv, const char *className, const char *methodName, const char *jvmMethodSignature);
			static jclass getClass(const char *className);
		};
	}
}

#endif
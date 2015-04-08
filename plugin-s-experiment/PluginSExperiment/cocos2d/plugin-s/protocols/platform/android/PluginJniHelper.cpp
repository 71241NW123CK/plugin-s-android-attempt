/*
 * todo: legal mumbo jumbo
 */

#include "PluginJniHelper.h"
#include <string>


#define DEBUG_LOG_ENABLED
#if DEBUG_LOG_ENABLED
#define LOG_TAG "PluginJniHelper"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#else
#endif

namespace scopely
{
	namespace plugin_s
	{
		JavaVM *PluginJniHelper::sharedJavaVM = NULL;
		jmethodID PluginJniHelper::sharedLoadClassMethodID = NULL;
		jobject PluginJniHelper::sharedClassLoader = NULL;

#pragma mark - public methods

		JavaVM *PluginJniHelper::getJavaVM()
		{
			return sharedJavaVM;
		}

		void PluginJniHelper::setJavaVM(JavaVM *javaVM)
		{
			sharedJavaVM = javaVM;
		}

		JNIEnv *PluginJniHelper::getJNIEnv()
		{
			if (!sharedJavaVM)
			{
				LOGD("JavaVM is NULL.");
				return NULL;
			}
			JNIEnv *result = NULL;
			if (sharedJavaVM->GetEnv((void **) &result, JNI_VERSION_1_4) != JNI_OK)
			{
				LOGD("Failed to get the environment using GetEnv().");
				return NULL;
			}
			if (sharedJavaVM->AttachCurrentThread(&result, 0) < 0)
			{
				LOGD("Failed to get the environment using AttachCurrentThread().");
				return NULL;
			}
			return result;
		}

		bool PluginJniHelper::getStaticMethodInfo(JNIEnv **pJNIEnv, jclass *pJclass, jmethodID *pJmethodID, const char *className, const char *methodName, const char *jvmMethodSignature)
		{
			if (className == NULL || methodName == NULL || jvmMethodSignature == NULL)
			{
				LOGD("Trying to get method info without class name, method name, and JVM method signature.");
				return false;
			}

			if (!(*pJNIEnv = getJNIEnv()))
			{
				LOGD("Failed to get the environment");
				return false;
			}

			if (!(*pJclass = getClass(className)))
			{
				LOGD("Failed to get class named %s.", className);
				return false;
			}

			if (!(*pJmethodID = (*pJNIEnv)->GetStaticMethodID(*pJclass, methodName, jvmMethodSignature)))
			{
				if ((*pJNIEnv)->ExceptionCheck())
				{
					(*pJNIEnv)->ExceptionClear();
				}
				LOGD("Failed to find method ID for static method with name %s and JVM method signature %s in class %s.", methodName, jvmMethodSignature, className);
				return false;
			}

			return true;
		}

		bool PluginJniHelper::getMethodInfo(JNIEnv **pJNIEnv, jclass *pJclass, jmethodID *pJmethodID, const char *className, const char *methodName, const char *jvmMethodSignature)
		{
			if (className == NULL || methodName == NULL || jvmMethodSignature == NULL)
			{
				LOGD("Trying to get method info without class name, method name, and JVM method signature.");
				return false;
			}

			if (!(*pJNIEnv = getJNIEnv()))
			{
				LOGD("Failed to get the environment");
				return false;
			}

			if (!(*pJclass = getClass(className)))
			{
				LOGD("Failed to get class named %s.", className);
				return false;
			}

			if (!(*pJmethodID = (*pJNIEnv)->GetMethodID(*pJclass, methodName, jvmMethodSignature)))
			{
				if ((*pJNIEnv)->ExceptionCheck())
				{
					(*pJNIEnv)->ExceptionClear();
				}
				LOGD("Failed to find method ID for instance method with name %s and JVM method signature %s in class %s.", methodName, jvmMethodSignature, className);
				return false;
			}

			return true;
		}

		std::string PluginJniHelper::stringForJstring(jstring aJstring)
		{
			if (aJstring == NULL) {
				return NULL;
			}

			JNIEnv *jniEnv = PluginJniHelper::getJNIEnv();
			if (!jniEnv)
			{
				return NULL;
			}

			const char *cStr = jniEnv->GetStringUTFChars(aJstring, NULL);
			std::string result(cStr);
			jniEnv->ReleaseStringUTFChars(aJstring, cStr);
			return result;
		}

		bool PluginJniHelper::setClassLoaderFromNativeActivity(jobject nativeActivity)
		{
			JNIEnv *jniEnv = getJNIEnv();
			jmethodID getClassLoaderMethodID = getMethodIDWithDefaultClassLoader(jniEnv, "android/app/NativeActivity", "getClassLoader", "()Ljava/lang/ClassLoader;");
			if (!getClassLoaderMethodID)
			{
				LOGD("failed to get class loader method ID from android.app.NativeActivity.");
				return false;
			}

			jobject classLoader = jniEnv->CallObjectMethod(nativeActivity, getClassLoaderMethodID);

			if (!classLoader)
			{
				LOGD("failed to get a class loader using android.app.NativeActivity#getClassLoader().");
				return false;
			}

			jmethodID loadClassMethodID = getMethodIDWithDefaultClassLoader(jniEnv, "java/lang/ClassLoader", "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
			if (!loadClassMethodID)
			{
				LOGD("failed to get method ID for java.lang.ClassLoader#loadClass(String).");
				return false;
			}

			sharedClassLoader = classLoader;
			sharedLoadClassMethodID = loadClassMethodID;
			return true;
		}

#pragma mark - private methods

		jmethodID PluginJniHelper::getMethodIDWithDefaultClassLoader(JNIEnv *jniEnv, const char *className, const char *methodName, const char *jvmMethodSignature)
		{
			if (!jniEnv || !className || !methodName || !jvmMethodSignature)
			{
				LOGD("Trying to get method ID without JNI environment, class name, method name, and JVM method signature.");
				return NULL;
			}

			jclass aJclass = jniEnv->FindClass(className);
			if (!aJclass)
			{
				LOGD("Failed to find class with name %s." className);
				return NULL;
			}

			jmethodID result;
			if (!(result = jniEnv->GetMethodID(aJclass, methodName, jvmMethodSignature)))
			{
				LOGD("Failed to find method with name %s with JVM method signature %s in class %s", methodName, jvmMethodSignature, className);
			}

			jniEnv->DeleteLocalRef(aJclass);
			return result;
		}

		jclass PluginJniHelper::getClass(const char *className)
		{
			if (!className)
			{
				return NULL;
			}
			JNIEnv *jniEnv = getJNIEnv();
			if (!jniEnv)
			{
				LOGD("Failed to get JNI environment.");
				return NULL;
			}
			jclass result = NULL;
			if (sharedClassLoader && sharedLoadClassMethodID)
			{
				jstring classNameJstring = jniEnv->NewStringUTF(className);
				if (!(result = (jclass) jniEnv->CallObjectMethod(sharedClassLoader, sharedLoadClassMethodID, classNameJstring)))
				{
					LOGD("Class loader failed to find class with name %s", className);
				}
				jniEnv->DeleteLocalRef(classNameJstring);
			}
			else
			{
				if (!(result = jniEnv->FindClass(className)))
				{
					LOGD("Failed to find class with name %s through JNIEnv FindClass function.");
				}
			}
			return result;
		}
	}
}
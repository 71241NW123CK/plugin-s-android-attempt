/*
 * todo: legal mumbo jumbo
 */

#include <jni.h>
#include "JniMacros.h"
#include "PluginJniHelper.h"
#include "PluginInstanceMap.h"

namespace scopely
{
	namespace plugin_s
	{
		PluginValue *Plugin::invokeMethodWithVariadicArgs(std::string objectiveCMethodName, std::string androidJavaMethodName, PluginValue::Type returnType, std::string androidJavaMethodJvmSignature, ...)
		{
            std::vector<PluginValue *> arguments;
            va_list argp;
            va_start(argp, androidJavaMethodJvmSignature);
            PluginValue *arg;
            while ((arg = va_arg(argp, PluginValue *)))
            {
                arguments.push_back(arg);
            }
            return invokeMethodWithVectorArgs(objectiveCMethodName, androidJavaMethodName, returnType, androidJavaMethodJvmSignature, arguments);
        }

		PluginValue *Plugin::invokeMethodWithVectorArgs(std::string objectiveCMethodName, std::string androidJavaMethodName, PluginValue::Type returnType, std::string androidJavaMethodJvmSignature, std::vector<PluginValue *> argumentVector)
		{
			int i;
			jclass aJclass;
			jmethodID aJmethodID;
			bool hasMethodID;
			JNIEnv *jniEnv = PluginJniHelper::getJNIEnv();
			if (!jniEnv)
			{
				LOGD("Failed to get JNI environment.");
				return NULL;
			}
			std::string className = PluginInstanceMap::getPluginJavaClassName(this);
			if (className == "")
			{
				LOGD("no class name for plugin.");
				return NULL;
			}
			jobject pluginObject = PluginInstanceMap::getPluginObject(this);
			int argumentVectorSize = argumentVector.size();
			jvalue *arguments = (jvalue *) malloc(sizeof(jvalue) * argumentVectorSize);
			// std::vector<jobject> jobjectArgumentVector;
			bool allArgsValid = true;
			PluginValue *result = NULL;

			for (i = 0; i < argumentVectorSize; i++)
			{
				PluginValue *argumentPluginValue = argumentVector[i];
				switch (argumentPluginValue->getType())
				{
					case PluginValue::Type::kTypeNone:
					case PluginValue::Type::kTypeVoid:
					{
						LOGD("invalid argument type");
						allArgsValid = false;
						break;
					}
					case PluginValue::Type::kTypeBool:
					{
						jboolean argumentJboolean = argumentPluginValue->getBoolValue();
						arguments[i].z = argumentJboolean;
						break;
					}
					case PluginValue::Type::kTypeInt:
					{
						jint argumentJint = argumentPluginValue->getIntValue();
						arguments[i].i = argumentJint;
						break;
					}
					case PluginValue::Type::kTypeFloat:
					{
						jfloat argumentJfloat = argumentPluginValue->getFloatValue();
						arguments[i].f = argumentJfloat;
						break;
					}
					case PluginValue::Type::kTypeString:
					{
						jstring argumentJstring = jniEnv->NewStringUTF(argumentPluginValue->getStringValue().c_str());
						arguments[i].l = argumentJstring;
						break;
					}
					default:
					{
						LOGD("lolwut.0");
						allArgsValid = false;
						break;
					}
				}
			}
			if (!allArgsValid)
			{
				LOGD("not all args valid.");
			}
			else if (!(hasMethodID = PluginJniHelper::getMethodInfo(jniEnv, &aJclass, &aJmethodID, className.c_str(), androidJavaMethodName.c_str(), androidJavaMethodJvmSignature.c_str())))
			{
				LOGD("Failed to get method info for method %s#%s (%s)", className.c_str(), androidJavaMethodName.c_str(), androidJavaMethodJvmSignature.c_str());
			}
			else
			{
				switch (returnType)
				{
					case PluginValue::Type::kTypeNone:
					{
						LOGD("invalid return type.");
						result = NULL;
						break;
					}
					case PluginValue::Type::kTypeVoid:
					{
						jniEnv->CallVoidMethodA(pluginObject, aJmethodID, arguments);
						result = PluginValue::nullValue(PluginValue::Type::kTypeVoid);
						break;
					}
					case PluginValue::Type::kTypeBool:
					{
						jboolean resultJboolean = jniEnv->CallBooleanMethodA(pluginObject, aJmethodID, arguments);
						result = PluginValue::valueWithBool(resultJboolean);
						break;
					}
					case PluginValue::Type::kTypeInt:
					{
						jint resultJint = jniEnv->CallIntMethodA(pluginObject, aJmethodID, arguments);
						result = PluginValue::valueWithInt(resultJint);
						break;
					}
					case PluginValue::Type::kTypeFloat:
					{
						jfloat resultJfloat = jniEnv->CallFloatMethodA(pluginObject, aJmethodID, arguments);
						result = PluginValue::valueWithFloat(resultJfloat);
						break;
					}
					default:
					{
						LOGD("lolwut.1");
						result = NULL;
					}
				}
			}
			jniEnv->DeleteLocalRef(aJclass);
			free(arguments);
			return result;
		}
	}
}

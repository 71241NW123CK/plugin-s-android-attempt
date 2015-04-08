/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_Plugin_h
#define Protocol_Plugin_h

#include <string>
#include <vector>
#include "PluginValue.h"

namespace scopely
{
	namespace plugin_s
	{
		class Plugin
		{
		public:
			//todo: do the method below.
			//PluginValue *invokeMethodWithVariadicArgs(std::string objectiveCMethodName, std::string androidJavaMethodName, ...);
			PluginValue *invokeMethodWithVariadicArgs(std::string objectiveCMethodName, std::string androidJavaMethodName, PluginValue::Type returnType, std::string androidJavaMethodJvmSignature, ...);
		private:
			PluginValue *invokeMethodWithVectorArgs(std::string objectiveCMethodName, std::string androidJavaMethodName, PluginValue::Type returnType, std::string androidJavaMethodJvmSignature, std::vector<PluginValue *> argumentVector);
		};
	}
}

#endif
/*
 * todo: legal mumbo jumbo
 */

#include "APlugin.h"
#include "PluginManager.h"

namespace scopely
{
	namespace plugin_s
	{
		APlugin::APlugin() {}

		APlugin::~APlugin() {}

		APlugin *APlugin::getSharedInstance()
		{
			static bool isInitialized = false;
			if (!isInitialized)
			{
				PluginManager::loadPlugin("APlugin", "NSAbstractRidiculousNameForAClassObjectProxyFactory", "com/scopely/services/a/A");
				isInitialized = true;
			}
			return (APlugin *) PluginManager::getPlugin("APlugin");
		}

		void APlugin::voidValuedMethod()
		{
			invokeMethodWithVariadicArgs("voidValuedMethod", "voidValuedMethod", PluginValue::Type::kTypeVoid, "()V");
		}

		bool APlugin::boolValuedMethod()
		{
			return invokeMethodWithVariadicArgs("boolValuedMethod", "boolValuedMethod", PluginValue::Type::kTypeBool, "()Z")->getBoolValue();
		}

		int APlugin::intValuedMethod()
		{
			return invokeMethodWithVariadicArgs("intValuedMethod", "intValuedMethod", PluginValue::Type::kTypeInt, "()I")->getIntValue();
		}

		std::string APlugin::stringValuedMethod()
		{
			return invokeMethodWithVariadicArgs("stringValuedMethod", "stringValuedMethod", PluginValue::Type::kTypeString, "()Ljava/lang/String;")->getStringValue();
		}
	}
}

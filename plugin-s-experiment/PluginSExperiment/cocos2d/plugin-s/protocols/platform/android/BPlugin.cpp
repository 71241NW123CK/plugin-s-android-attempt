/*
 * todo: legal mumbo jumbo
 */

#include "BPlugin.h"
#include "PluginManager.h"

namespace scopely
{
	namespace plugin_s
	{
		BPlugin::BPlugin() {}

		BPlugin::~BPlugin() {}

		BPlugin *BPlugin::getSharedInstance()
		{
			static bool isInitialized = false;
			if (!isInitialized)
			{
				PluginManager::loadPlugin("BPlugin", "NSAbstractRidiculousNameForAClassObjectProxyFactory", "com/scopely/services/b/B");
				isInitialized = true;
			}
			return (BPlugin *) PluginManager::getPlugin("BPlugin");
		}

		void BPlugin::voidValuedMethod()
		{
			invokeMethodWithVariadicArgs("voidValuedMethod", "voidValuedMethod", PluginValue::Type::kTypeVoid, "()V");
		}

		bool BPlugin::boolValuedMethod()
		{
			return invokeMethodWithVariadicArgs("boolValuedMethod", "boolValuedMethod", PluginValue::Type::kTypeBool, "()Z")->getBoolValue();
		}

		int BPlugin::intValuedMethod()
		{
			return invokeMethodWithVariadicArgs("intValuedMethod", "intValuedMethod", PluginValue::Type::kTypeInt, "()I")->getIntValue();
		}

		std::string BPlugin::stringValuedMethod()
		{
			return invokeMethodWithVariadicArgs("stringValuedMethod", "stringValuedMethod", PluginValue::Type::kTypeString, "()Ljava/lang/String;")->getStringValue();
		}
	}
}

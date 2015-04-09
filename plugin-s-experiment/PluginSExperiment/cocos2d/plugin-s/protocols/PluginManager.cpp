/*
 * todo: legal mumbo jumbo
 */

#include <map>
#include "JniMacros.h"
#include "PluginManager.h"
#include "PluginFactory.h"
#include "PluginInstanceMap.h"

namespace scopely
{
    namespace plugin_s
    {
        static std::map<std::string, Plugin *> sharedStringPluginMap;

        void PluginManager::loadPlugin(std::string pluginName, std::string objectiveCComponentClassName, std::string androidJavaComponentClassName)
        {
            if (getPlugin(pluginName))
            {
                return;
            }
            Plugin *plugin = PluginFactory::createPlugin(pluginName, objectiveCComponentClassName, androidJavaComponentClassName);
            if (!plugin)
            {
                LOGD("Failed to create plugin with name %s, Objective-C component class name %s, Android Java component class name %s", pluginName.c_str(), objectiveCComponentClassName.c_str(), androidJavaComponentClassName.c_str());
                return;
            }
            setPlugin(pluginName, plugin);
        }

        Plugin *PluginManager::getPlugin(std::string pluginName)
        {
            std::map<std::string, Plugin *>::const_iterator iterator = sharedStringPluginMap.find(pluginName);
            return iterator == sharedStringPluginMap.end() ? NULL : iterator->second;
        }

        void PluginManager::setPlugin(std::string name, Plugin *plugin)
        {
            sharedStringPluginMap[name] = plugin;
        }
    }
}

/*
 * todo: legal mumbo jumbo
 */

#include <map>
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
            PluginFactory::createPlugin(pluginName, objectiveCComponentClassName, androidJavaComponentClassName);
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

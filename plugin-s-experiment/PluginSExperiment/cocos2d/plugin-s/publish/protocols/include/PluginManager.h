/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_PluginManager_h
#define Protocol_PluginManager_h

#include "Plugin.h"

namespace scopely
{
    namespace plugin_s
    {
        class PluginManager
        {
        public:
            static void loadPlugin(std::string pluginName, std::string objectiveCComponentClassName, std::string androidJavaComponentClassName);
            static Plugin *getPlugin(std::string pluginName);
        private:
            static void setPlugin(std::string name, Plugin *plugin);
        };
    }
}

#endif
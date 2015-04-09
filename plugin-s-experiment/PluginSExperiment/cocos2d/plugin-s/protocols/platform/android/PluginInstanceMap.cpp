/*
 * todo: legal mumbo jumbo
 */

#include <map>
#include "PluginInstanceMap.h"

namespace scopely
{
	namespace plugin_s
	{
		static std::map<Plugin *, jobject> sharedPluginJobjectMap;
		static std::map<Plugin *, std::string> sharedPluginStringMap;

		void PluginInstanceMap::setPluginObject(Plugin *plugin, jobject object)
		{
			sharedPluginJobjectMap[plugin] = object;			
		}

		jobject PluginInstanceMap::getPluginObject(Plugin *plugin)
		{
			std::map<Plugin *, jobject>::const_iterator iterator = sharedPluginJobjectMap.find(plugin);
			return iterator == sharedPluginJobjectMap.end() ? NULL : iterator->second;
		}

		void PluginInstanceMap::setPluginJavaClassName(Plugin *plugin, std::string javaClassName)
		{
			sharedPluginStringMap[plugin] = javaClassName;
		}

		std::string PluginInstanceMap::getPluginJavaClassName(Plugin *plugin)
		{
			std::map<Plugin *, std::string>::const_iterator iterator = sharedPluginStringMap.find(plugin);
			return iterator == sharedPluginStringMap.end() ? NULL : iterator->second;
		}
	}
}
/*
 * todo: legal mumbo jumbo
 */

#include <map>
#include "PluginInstanceMap.h"

namespace scopely
{
	namespace plugin_s
	{
		static map<Plugin *, jobject> sharedPluginJobjectMap;

		void PluginInstanceMap::setPluginObject(Plugin *plugin, jobject object)
		{
			sharedPluginJobjectMap[plugin] = object;			
		}

		jobject PluginInstanceMap::getPluginObject(Plugin *plugin)
		{
			map<Plugin *, jobject>::const_iterator iterator = sharedPluginJobjectMap.find(plugin);
			return iterator == sharedPluginJobjectMap.end() ? NULL : iterator->second;
		}
	}
}
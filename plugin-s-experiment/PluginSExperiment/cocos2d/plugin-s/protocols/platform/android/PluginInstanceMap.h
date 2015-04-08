/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_PluginInstanceMap_h
#define Protocol_PluginInstanceMap_h

#include <jni.h>
#include <string>
#include "Plugin.h"

namespace scopely
{
	namespace plugin_s
	{
		class PluginInstanceMap
		{
		public:
			static void setPluginObject(Plugin *plugin, jobject object);
			static jobject getPluginObject(Plugin *plugin);
			static void setPluginJavaClassName(Plugin *plugin, std::string javaClassName);
			static std::string getPluginJavaClassName(Plugin *plugin);
		};
	}
}

#endif
/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_PluginFactory_h
#define Protocol_PluginFactory_h

#include <string>

namespace scopely
{
	namespace plugin_s
	{
		class PluginFactory
		{
		public:
			static void createPlugin(std::string name, std::string objectiveCComponentClassName, std::string androidJavaComponentClassName);
		};
	}
}

#endif
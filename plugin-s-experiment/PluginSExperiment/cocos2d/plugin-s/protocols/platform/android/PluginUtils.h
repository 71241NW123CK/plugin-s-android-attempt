/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocols_PluginUtils_h
#define Protocols_PluginUtils_h

#include <android_native_app_glue.h>

namespace scopely
{
	namespace plugin_s
	{
		class PluginUtils
		{
		public:
			static bool initializePluginSystem(android_app *androidApp);
		};
	}
}

#endif
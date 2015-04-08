/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_APlugin_h
#define Protocol_APlugin_h

#include "Plugin.h"

namespace scopely
{
	namespace plugin_s
	{
		class APlugin : public Plugin
		{
		public:
			APlugin();
			virtual ~APlugin();
			static APlugin *getSharedInstance();
			void voidValuedMethod();
			int intValuedMethod();
			std::string stringValuedMethod();
		};
	}
}

#endif
/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_BPlugin_h
#define Protocol_BPlugin_h

#include "Plugin.h"

namespace scopely
{
	namespace plugin_s
	{
		class BPlugin : public Plugin
		{
		public:
			BPlugin();
			virtual ~BPlugin();
			static BPlugin *getSharedInstance();
			void voidValuedMethod();
			int intValuedMethod();
			std::string stringValuedMethod();
		};
	}
}

#endif
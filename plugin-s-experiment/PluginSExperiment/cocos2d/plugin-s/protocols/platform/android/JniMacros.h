/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_JniMacros_h
#define Protocol_JniMacros_h

#define DEBUG_LOG_ENABLED
#if DEBUG_LOG_ENABLED
#define LOG_TAG "PluginSNative"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#else
#endif

#endif

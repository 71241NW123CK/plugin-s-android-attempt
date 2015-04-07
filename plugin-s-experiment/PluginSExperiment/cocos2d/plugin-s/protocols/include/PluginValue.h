/*
 * todo: legal mumbo jumbo
 */

#ifndef Protocol_PluginValue_h
#define Protocol_PluginValue_h

namespace scopely
{
    namespace plugin_s
    {
        class PluginValue;
        //todo: more types!  use some typedefs
        class PluginValue
        {
        public:
            typedef enum Type
            {
                kTypeNone,
                kTypeVoid,
                kTypeBool,
                kTypeInt,
                kTypeFloat,
                kTypeString,
            } Type;

            static PluginValue *nullValue(Type valueType);
            //todo: nullability!
            static PluginValue *valueWithBool(bool boolValue);
            static PluginValue *valueWithInt(int intValue);
            static PluginValue *valueWithFloat(float floatValue);
            static PluginValue *valueWithString(std::string stringValue);
            inline Type getType() { return _type; }
            inline bool getBoolValue() { return _boolValue; }
            inline int getIntValue() { return _intValue; }
            inline float getFloatValue() { return _floatValue; }
            inline std::string getStringValue() { return _stringValue; }
        private:
            Type _type;
            bool _boolValue;
            int _intValue;
            float _floatValue;
            std::string _stringValue;
            PluginValue(Type type);
            PluginValue *withBoolValue(bool boolValue);
            PluginValue *withIntValue(int intValue);
            PluginValue *withFloatValue(float floatValue);
            PluginValue *withStringValue(std::string stringValue);
        };
    }
}

#endif
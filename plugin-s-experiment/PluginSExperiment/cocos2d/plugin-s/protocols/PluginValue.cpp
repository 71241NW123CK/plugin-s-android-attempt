/*
 * todo: legal mumbo jumbo
 */

#include "PluginValue"

namespace scopely
{
    namespace plugin_s
    {
        PluginValue *PluginValue::nullValue(Type valueType)
        {
            return new PluginValue(valueType);
        }
        
        PluginValue *PluginValue::valueWithBool(bool boolValue)
        {
            return (new PluginValue(kTypeBool))->withBoolValue(boolValue);
        }
        
        PluginValue *PluginValue::valueWithInt(int intValue)
        {
            return (new PluginValue(kTypeInt))->withIntValue(intValue);
        }
        
        PluginValue *PluginValue::valueWithFloat(float floatValue)
        {
            return (new PluginValue(kTypeFloat))->withFloatValue(floatValue);
        }
        
        PluginValue *PluginValue::valueWithString(std::string stringValue)
        {
            return (new PluginValue(kTypeString))->withStringValue(stringValue);
        }
        
        PluginValue::PluginValue(Type type) : _type(type) {}
        
        PluginValue *PluginValue::withBoolValue(bool boolValue) { _boolValue = boolValue; return this; }
        
        PluginValue *PluginValue::withIntValue(int intValue) { _intValue = intValue; return this; }
        
        PluginValue *PluginValue::withFloatValue(float floatValue) { _floatValue = floatValue; return this; }
        
        PluginValue *PluginValue::withStringValue(std::string stringValue) { _stringValue = stringValue; return this; }
    }
}
#pragma once

#ifndef _FLAGS_
#define _FLAGS_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "structures/flag.h"

#define DECLARE_FLAG(flagName, _value)                                                              \
public:                                                                                             \
    bool get##flagName() const { return flags.at(STRING_LITERAL(#flagName)).value; }                \
    void set##flagName(bool value) { String key = STRING_LITERAL(#flagName); flags[key].value = value; }  \
    bool get##flagName##DefaultValue() const { return flags.at(STRING_LITERAL(#flagName)).defaultValue; } \
private:                                                                                            \
    struct FlagRegistrar_##flagName {                                                               \
        FlagRegistrar_##flagName(StringMap<Flag>& f) {                                              \
            String key = STRING_LITERAL(#flagName);                                                 \
            f[key].value = _value;                                                                  \
            f[key].defaultValue = _value;                                                           \
        }                                                                                           \
    } flagRegistrar_##flagName = FlagRegistrar_##flagName(flags);

namespace lotus {

    class LOTUS_API Flags {
        StringMap<Flag> flags;

    public:

        Flags() = default;

        void set(const String& key, bool value);

        void setDefault(const String& key);

        bool get(const String& key) const;

        bool getDefault(const String& key) const;

        bool isExistsWithError(const String& key) const;

        DECLARE_FLAG(ImportEverythingWithSameName, true);
    };
}

#endif // _FLAGS_
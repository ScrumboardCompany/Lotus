#pragma once

#ifndef _FLAGS_
#define _FLAGS_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"

#define DECLARE_FLAG(flagName, defaultValue)                                                        \
public:                                                                                             \
    bool get##flagName() const { return flags.at(STRING_LITERAL(#flagName)); }                      \
    void set##flagName(bool value) { String key = STRING_LITERAL(#flagName); flags[key] = value; }  \
private:                                                                                            \
    struct FlagRegistrar_##flagName {                                                               \
        FlagRegistrar_##flagName(StringMap<bool>& f) {                                              \
            String key = STRING_LITERAL("AllowOverwrite");                                          \
            f[key] = (defaultValue);                                                                \
        }                                                                                           \
    } flagRegistrar_##flagName = FlagRegistrar_##flagName(flags);

namespace lotus {

	class Flags {
		StringMap<bool> flags;

	public:

		Flags() = default;

        void set(const String& key, bool value);

        bool isExistsWithError(const String& key) const;

        DECLARE_FLAG(AllowOverwrite, true);
	};
}

#endif // _FLAGS_
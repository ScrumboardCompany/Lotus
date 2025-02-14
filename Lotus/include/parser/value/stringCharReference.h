#pragma once

#ifndef _STRINGCHARREFERENCEVALUE_
#define _STRINGCHARREFERENCEVALUE_

#include "parser/value/value.h"

namespace lotus {

    class StringValue;

    class StringCharReference : public IValue {
        StringValue& parent;
        int index;

    public:
        StringCharReference(StringValue& parent, int index);

        String asString() override;

        StringCharReference& set(const Value& other);
        Value sizeInRam() override;
    };

}

#endif // _STRINGCHARREFERENCEVALUE_
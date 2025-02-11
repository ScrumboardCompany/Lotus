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

        String getType() const override;

        StringCharReference& set(const Value& other);
    };

}

#endif // _STRINGCHARREFERENCEVALUE_
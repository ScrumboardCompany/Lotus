#include "parser/value/stringCharReference.h"
#include "parser/value/stringValue.h"

using namespace lotus;

lotus::StringCharReference::StringCharReference(StringValue& parent, int index) : parent(parent), index(index) {}

String lotus::StringCharReference::asString() {
    return String(1, parent.value[index]);
}

String lotus::StringCharReference::getType() const {
    return STRING_LITERAL("char_reference");
}

StringCharReference& lotus::StringCharReference::set(const Value& other) {
    String value = other->asString();
    if (value.empty()) parent.value.clear();

    parent.value[index] = value[0];
    return *this;
}

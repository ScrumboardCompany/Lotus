#include "parser/value/stringCharReference.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "parser/function/function.h"

using namespace lotus;

lotus::StringCharReference::StringCharReference(StringValue& parent, int index) : parent(parent), index(index) {
    type = STRING_LITERAL("char_reference");
}

String lotus::StringCharReference::asString() {
    return String(1, parent.value[index]);
}

StringCharReference& lotus::StringCharReference::set(const Value& other) {
    String value = other->asString();
    if (value.empty()) parent.value.clear();

    parent.value[index] = value[0];
    return *this;
}

Value lotus::StringCharReference::sizeInRam() {
    return INT(sizeof(StringCharReference));
}
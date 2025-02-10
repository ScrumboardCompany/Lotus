#include "parser/value/arrayValue.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::ArrayValue::ArrayValue(std::vector<Value> elements) : elements(elements) {}

String lotus::ArrayValue::asString() {
    String result = STRING_LITERAL("[");

    for (size_t i = 0; i < elements.size(); i++) {
        result += elements[i]->asString();
        if (i < elements.size() - 1) {
            result += STRING_LITERAL(", ");
        }
    }
    return result;
}

String lotus::ArrayValue::getType() const {
	return STRING_LITERAL("array");
}

Value lotus::ArrayValue::add(const Value& other) {
    if (other->getType() == STRING_LITERAL("array")) {
        std::vector<Value> newElements = elements;

        Ptr<ArrayValue> value = std::dynamic_pointer_cast<ArrayValue>(other);
        if (!value) {
            throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Dynamic cast to ArrayValue failed"));
        }

        for (auto& el : value->elements) {
            newElements.push_back(el);
        }

        return ARRAY(newElements);
    }
    throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
    return Value();
}
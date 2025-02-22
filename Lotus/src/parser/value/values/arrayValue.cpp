#include "parser/value/arrayValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"

using namespace lotus;

lotus::ArrayValue::ArrayValue(std::vector<Value> elements) : elements(elements) {
    type = STRING_LITERAL("array");
}

String lotus::ArrayValue::asString() {
    String result;

    for (size_t i = 0; i < elements.size(); i++) {
        result += elements[i]->asString();
        if (i < elements.size() - 1) {
            result += STRING_LITERAL(", ");
        }
    }
    return result;
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
}

Value lotus::ArrayValue::addSet(const Value& other) {
    if (auto arr = std::dynamic_pointer_cast<ArrayValue>(add(other))) {
        elements = arr->elements;
    }
    return ARRAY(elements);
}

void lotus::ArrayValue::foreach(const String& name, const Statement& body, Variables& variables) {

    for (size_t i = 0; i < elements.size(); i++) {
        variables.set(name, elements[i]);
        try {
            body->execute();
        }
        catch (const ContinueStatement&) {
            continue;
        }
        catch (const BreakStatement&) {
            break;
        }

    }

}

Value& lotus::ArrayValue::index(const Value& index) {
    checkThrowIndexError(index, elements.size());
    return elements[index->asInt()];
}

Value lotus::ArrayValue::size() {
    return INT(elements.size());
}

Value lotus::ArrayValue::sizeInRam() {
    return INT(sizeof(ArrayValue));
}
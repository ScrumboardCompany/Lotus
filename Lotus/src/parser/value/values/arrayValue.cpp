#include "parser/value/arrayValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/module.h"

using namespace lotus;

lotus::ArrayValue::ArrayValue(std::vector<Value> elements) : elements(elements) {
    type = STRING_LITERAL("array");
}

String lotus::ArrayValue::asString(Module& module) {
    String result;

    for (size_t i = 0; i < elements.size(); i++) {
        result += elements[i]->asString(module);
        if (i < elements.size() - 1) {
            result += STRING_LITERAL(", ");
        }
    }
    return result;
}

Value lotus::ArrayValue::add(const Value& other, Module&) {
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

Value lotus::ArrayValue::addSet(const Value& other, Module& module) {
    if (auto arr = std::dynamic_pointer_cast<ArrayValue>(add(other, module))) {
        elements = arr->elements;
    }
    return ARRAY(elements);
}

void lotus::ArrayValue::foreach(const String& name, const Statement& body, Module& module) {

    for (size_t i = 0; i < elements.size(); i++) {
        module.variables.set(name, elements[i]);
        try {
            body->execute(module);
        }
        catch (const ContinueStatement&) {
            continue;
        }
        catch (const BreakStatement&) {
            break;
        }

    }

}

Value lotus::ArrayValue::getOfIndex(const Value& index, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, elements.size(), module);
        return elements[index->asInt(module)];
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::ArrayValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, elements.size(), module);
        elements[index->asInt(module)] = other;
        return elements[index->asInt(module)];
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::ArrayValue::size(Module&) {
    return INT(static_cast<int>(elements.size()));
}

Value lotus::ArrayValue::sizeInRam() {
    return INT(static_cast<int>(sizeof(*this)));
}
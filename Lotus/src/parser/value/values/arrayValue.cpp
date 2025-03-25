#include "parser/value/arrayValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "parser/function/function.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/module.h"

using namespace lotus;

lotus::ArrayValue::ArrayValue(const std::vector<Value>& elements, Module& module) : elements(elements) {
    type = STRING_LITERAL("array");

    declareMethod(STRING_LITERAL("push"), METHOD(AccessModifierType::PUBLIC, [&] {
        this->elements.push_back(module.GET("element"));
        }, "element"));

    declareMethod(STRING_LITERAL("push"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("index")->instanceOf("int")) module.THROW(STRING("Index can be only int"), STRING("type_error"));
        Int index = module.GET("index")->asInt(module);
        if (index > static_cast<Int>(this->elements.size())) module.THROW(STRING("Index is bigger than array size"), STRING("out_of_range"));
        if (index < 0) module.THROW(STRING("Index can't be less than 0"), STRING("out_of_range"));
        this->elements.insert(this->elements.begin() + static_cast<int>(index), module.GET("element"));
        }, "element", "index"));

    declareMethod(STRING_LITERAL("push"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("start")->instanceOf("int") || !module.GET("end")->instanceOf("int")) module.THROW(STRING("Index can be only int"), STRING("type_error"));
        Int start = module.GET("start")->asInt(module);
        Int end = module.GET("end")->asInt(module);
        Value value = module.GET("value");

        if (start > static_cast<Int>(this->elements.size())) module.THROW(STRING("Start index is bigger than array size"), STRING("out_of_range"));
        if (end > static_cast<Int>(this->elements.size())) module.THROW(STRING("End index is bigger than array size"), STRING("out_of_range"));
        if (start < 0) module.THROW(STRING("Start index can't be less than 0"), STRING("out_of_range"));
        if (end < 0) module.THROW(STRING("End index can't be less than 0"), STRING("out_of_range"));
        if (start > end) module.THROW(STRING("Start index can't be greater than end index"), STRING("out_of_range"));

        /*for (int i = start; i <= end; ++i) {
            this->elements[i] = value;
        }*/ // Replaces

        this->elements.insert(this->elements.begin() + static_cast<int>(start), static_cast<int>(end - start) + 1, value); // Adds
        }, "value", "start", "end"));

    declareMethod(STRING_LITERAL("pop"), METHOD(AccessModifierType::PUBLIC, [&] {
        this->elements.pop_back();
        }));

    declareMethod(STRING_LITERAL("pop"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("index")->instanceOf("int")) module.THROW(STRING("Index can be only int"), STRING("type_error"));
        Int index = module.GET("index")->asInt(module);
        if (index > static_cast<Int>(this->elements.size())) module.THROW(STRING("Index is bigger than array size"), STRING("out_of_range"));
        if (index < 0) module.THROW(STRING("Index can't be less than 0"), STRING("out_of_range"));
        this->elements.erase(this->elements.begin() + static_cast<int>(module.GET("index")->asInt(module)));
        }, "index"));

    declareMethod(STRING_LITERAL("pop"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("start")->instanceOf("int") || !module.GET("end")->instanceOf("int")) module.THROW(STRING("Index can be only int"), STRING("type_error"));
        Int start = module.GET("start")->asInt(module);
        Int end = module.GET("end")->asInt(module);

        if (start > static_cast<Int>(this->elements.size())) module.THROW(STRING("Start index is bigger than array size"), STRING("out_of_range"));
        if (end > static_cast<Int>(this->elements.size())) module.THROW(STRING("End index is bigger than array size"), STRING("out_of_range"));
        if (start < 0) module.THROW(STRING("Start index can't be less than 0"), STRING("out_of_range"));
        if (end < 0) module.THROW(STRING("End index can't be less than 0"), STRING("out_of_range"));
        if (start > end) module.THROW(STRING("Start index can't be greater than end index"), STRING("out_of_range"));

        this->elements.erase(this->elements.begin() + static_cast<int>(start), this->elements.begin() + static_cast<int>(end) + 1);
        }, "start", "end"));

    declareMethod(STRING_LITERAL("clear"), METHOD(AccessModifierType::PUBLIC, [&] {
        this->elements.clear();
        }));

    declareMethod(STRING_LITERAL("empty"), METHOD(AccessModifierType::PUBLIC, [&] {
        RETURN_VALUE(BOOL(this->elements.empty()));
        }));
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

Value lotus::ArrayValue::add(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("array")) {
        std::vector<Value> newElements = elements;

        Ptr<ArrayValue> value = std::dynamic_pointer_cast<ArrayValue>(other);
        if (!value) {
            throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Dynamic cast to ArrayValue failed"));
        }

        for (auto& el : value->elements) {
            newElements.push_back(el);
        }

        return ARRAY(newElements, module);
    }
    throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
}

Value lotus::ArrayValue::addSet(const Value& other, Module& module) {
    if (auto arr = std::dynamic_pointer_cast<ArrayValue>(add(other, module))) {
        elements = arr->elements;
    }
    return ARRAY(elements, module);
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
        return elements[static_cast<int>(index->asInt(module))];
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::ArrayValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, elements.size(), module);
        elements[static_cast<int>(index->asInt(module))] = other;
        return elements[static_cast<int>(index->asInt(module))];
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::ArrayValue::size(Module&) {
    return INT(static_cast<Int>(elements.size()));
}

Value lotus::ArrayValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::ARRAY(const std::vector<Value>& elements, Module& module) {
    return MAKE_PTR<ArrayValue>(elements, module);
}
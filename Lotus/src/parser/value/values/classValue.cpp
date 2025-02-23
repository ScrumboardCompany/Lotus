#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "parser/value/lambdaValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"

#include <iostream>

using namespace lotus;

bool lotus::ClassValue::hasField(const String& name) {
    if (fields.find(name) != fields.end()) return true;

    for (auto& parent : parents) {
        if (parent->hasField(name)) return true;
    }
    return false;
}

bool lotus::ClassValue::assignField(const String& name, const FieldMemberInfo& field) {
   if (fields.find(name) != fields.end()) {
        fields[name].value = field.value;
        return true;
    }
    
    for (auto& parent : parents) {
        if (parent->assignField(name, field)) return true;
    }

    return false;
}

int lotus::ClassValue::asInt(Variables& variables) {
    return callMethod(STRING_LITERAL("__asInt__"), {}, variables)->asInt(variables);
}

double lotus::ClassValue::asDouble(Variables& variables) {
    return callMethod(STRING_LITERAL("__asDouble__"), {}, variables)->asDouble(variables);
}

bool lotus::ClassValue::asBool(Variables& variables) {
    return callMethod(STRING_LITERAL("__asBool__"), {}, variables)->asBool(variables);
}

String lotus::ClassValue::asString(Variables& variables) {
    return callMethod(STRING_LITERAL("__asString__"), {}, variables)->asString(variables);
}

Value lotus::ClassValue::add(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__add__"), { other }, variables);
}

Value lotus::ClassValue::substract(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__substract__"), { other }, variables);
}

Value lotus::ClassValue::multiply(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__multiply__"), { other }, variables);
}

Value lotus::ClassValue::divide(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__divide__"), { other }, variables);
}

Value lotus::ClassValue::power(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__power__"), { other }, variables);
}

Value lotus::ClassValue::divideModule(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__divideModule__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseAnd(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseAnd__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseOr(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseOr__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseXor(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseXor__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseNot(Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseNot__"), {}, variables);
}

Value lotus::ClassValue::bitwiseLeftShift(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseLeftShift__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseRightShift(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseRightShift__"), { other }, variables);
}

Value lotus::ClassValue::greater(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__greater__"), { other }, variables);
}

Value lotus::ClassValue::less(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__less__"), { other }, variables);
}

Value lotus::ClassValue::greaterEqual(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__greaterEqual__"), { other }, variables);
}

Value lotus::ClassValue::lessEqual(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__lessEqual__"), { other }, variables);
}

Value lotus::ClassValue::equality(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__equality__"), { other }, variables);
}

Value lotus::ClassValue::inequality(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__inequality__"), { other }, variables);
}

Value lotus::ClassValue::logicalOr(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__logicalOr__"), { other }, variables);
}

Value lotus::ClassValue::logicalAnd(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__logicalAnd__"), { other }, variables);
}

Value lotus::ClassValue::addSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__addSet__"), { other }, variables);
}

Value lotus::ClassValue::substractSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__substractSet__"), { other }, variables);
}

Value lotus::ClassValue::multiplySet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__multiplySet__"), { other }, variables);
}

Value lotus::ClassValue::divideSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__divideSet__"), { other }, variables);
}

Value lotus::ClassValue::powerSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__powerSet__"), { other }, variables);
}

Value lotus::ClassValue::divideModuleSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__divideModuleSet__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseAndSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseAndSet__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseOrSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseOrSet__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseXorSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseXorSet__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseNotSet(Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseNotSet__"), {}, variables);
}

Value lotus::ClassValue::bitwiseLeftShiftSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseLeftShiftSet__"), { other }, variables);
}

Value lotus::ClassValue::bitwiseRightShiftSet(const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__bitwiseRightShiftSet__"), { other }, variables);
}

Value lotus::ClassValue::unaryPlus(Variables& variables) {
    return callMethod(STRING_LITERAL("__unaryPlus__"), {}, variables);
}

Value lotus::ClassValue::unaryMinus(Variables& variables) {
    return callMethod(STRING_LITERAL("__unaryMinus__"), {}, variables);
}

Value lotus::ClassValue::unaryNot(Variables& variables) {
    return callMethod(STRING_LITERAL("__unaryNot__"), {}, variables);
}

Value lotus::ClassValue::prefixIncrement(Variables& variables) {
    return callMethod(STRING_LITERAL("__prefixIncrement__"), {}, variables);
}

Value lotus::ClassValue::postfixIncrement(Variables& variables) {
    return callMethod(STRING_LITERAL("__postfixIncrement__"), {}, variables);
}

Value lotus::ClassValue::prefixDecrement(Variables& variables) {
    return callMethod(STRING_LITERAL("__prefixDecrement__"), {}, variables);
}

Value lotus::ClassValue::postfixDecrement(Variables& variables) {
    return callMethod(STRING_LITERAL("__postfixDecrement__"), {}, variables);
}

Value lotus::ClassValue::size(Variables& variables) {
    return callMethod(STRING_LITERAL("__size__"), {}, variables);
}

Value lotus::ClassValue::getOfIndex(const Value& index, Variables& variables) {
    return callMethod(STRING_LITERAL("__getOfIndex__"), {index}, variables);
}

Value lotus::ClassValue::setOfIndex(const Value& index, const Value& other, Variables& variables) {
    return callMethod(STRING_LITERAL("__setOfIndex__"), { index, other }, variables);
}

Value lotus::ClassValue::sizeInRam() {
    return INT(sizeof(ClassValue));
}

ClassValue& lotus::ClassValue::getMethod(const String& name, size_t argsCount, MethodMemberInfo& memberInfo) {
    if (methods.find(name) != methods.end()) {
        Ptr<MethodMemberInfo> variadic = nullptr;
        for (auto& method : methods[name]) {
            if (method.value.hasVariadic() && argsCount >= method.value.getArgsCount() - 1) variadic = MAKE_PTR<MethodMemberInfo>(method);
            if (method.value.getArgsCount() == argsCount) {
                memberInfo = method;
                break;
            }
        }
        if (variadic) memberInfo = *variadic;
        return *this;
    }

    for (auto& parent : parents) {
        try {
            MethodMemberInfo parentMemberInfo;
            ClassValue& parentClass = parent->getMethod(name, argsCount, parentMemberInfo);
            memberInfo = parentMemberInfo;
            return parentClass;
        }
        catch (const LotusException&) {
            continue;
        }
    }

    throw LotusException(STRING_LITERAL("Undefined method \"") + name + STRING_LITERAL("\""));
}

void lotus::ClassValue::declareField(const String& name, const FieldMemberInfo& memberInfo) {
    if (hasField(name)) throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" already exists"));
    fields.emplace(name, memberInfo);
}

void lotus::ClassValue::declareMethod(const String& name, const MethodMemberInfo& memberInfo) {
    if (methods.find(name) != methods.end()) {
        for (auto& method : methods[name]) {
            if (method.value.getArgsCount() == memberInfo.value.getArgsCount()) {
                throw LotusException(STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" with ") +
                    std::to_wstring(memberInfo.value.getArgsCount()) + STRING_LITERAL(" arguments already exists"));
            }
        }
        methods[name].emplace_back(memberInfo);
    }
    else {
        methods.emplace(name, std::vector<MethodMemberInfo>{memberInfo});
    }
}

Value& lotus::ClassValue::getField(const String& name) {
    if (fields.find(name) != fields.end()) {
        if (fields[name].accessModifier == AccessModifierType::PRIVATE) {
            throw LotusException(STRING_LITERAL("Request to private field: \"") + name + STRING_LITERAL("\""));
        }
        return fields[name].value;
    }

    for (auto& parent : parents) {
        if (parent->hasField(name)) {
            return parent->getField(name);
        }
    }

    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value ClassValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    if (fields.find(name) != fields.end()) {
        if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(getField(name))) {
            if (lambda->getArgsCount() == args.size()) return lambda->call(args, variables);
        }
    }

    MethodMemberInfo methodInfo;
    ClassValue& value = getMethod(name, args.size(), methodInfo);

    if (methodInfo.accessModifier == AccessModifierType::PRIVATE) {
        throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
    }

    ClassValue thisValue;
    thisValue.fields = value.fields;
    thisValue.methods = value.methods;
    thisValue.parents = value.parents;
    thisValue.type = value.getType();

    for (auto& field : thisValue.fields) {
        field.second.accessModifier = AccessModifierType::PUBLIC;
    }
    for (auto& methodVector : thisValue.methods) {
        for (auto& method : methodVector.second) {
            method.accessModifier = AccessModifierType::PUBLIC;
        }
    }

    variables.enterScope();
    variables.declare(STRING_LITERAL("this"), MAKE_PTR<ClassValue>(thisValue));
    Value returnValue = methodInfo.value.call(args, variables);

    if (auto thisValueAfterMethod = std::dynamic_pointer_cast<ClassValue>(variables.get(STRING_LITERAL("this")))) {

        value.fields = thisValueAfterMethod->fields;
        value.methods = thisValueAfterMethod->methods;
        value.parents = thisValueAfterMethod->parents;
    }

    variables.exitScope();
    return returnValue;
}
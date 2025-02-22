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

Value lotus::ClassValue::sizeInRam() {
    return INT(sizeof(ClassValue));
}

MethodMemberInfo lotus::ClassValue::getMethod(const String& name, size_t argsCount, ClassValue& value) {
    if (methods.find(name) != methods.end()) {
        value = *this;
        Ptr<MethodMemberInfo> variadic = nullptr;
        for (auto& method : methods[name]) {
            if (method.value.hasVariadic() && argsCount >= method.value.getArgsCount() - 1) variadic = MAKE_PTR<MethodMemberInfo>(method);
            if (method.value.getArgsCount() == argsCount) return method;
        }
        if (variadic) return *variadic;
    }

    for (auto& parent : parents) {
        try {
            ClassValue parentValue;
            auto methodInfo = parent->getMethod(name, argsCount, parentValue);

            value = parentValue;

            return methodInfo;
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

    Ptr<ClassValue> value = MAKE_PTR<ClassValue>();

    auto methodInfo = getMethod(name, args.size(), *value);
    if (methodInfo.accessModifier == AccessModifierType::PRIVATE) {
        throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
    }

    ClassValue thisValue;
    thisValue.fields = value->fields;
    thisValue.methods = value->methods;
    thisValue.parents = value->parents;
    thisValue.type = value->getType();

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

        value->fields = thisValueAfterMethod->fields;
        value->methods = thisValueAfterMethod->methods;
        value->parents = thisValueAfterMethod->parents;
    }

    variables.exitScope();
    return returnValue;
}
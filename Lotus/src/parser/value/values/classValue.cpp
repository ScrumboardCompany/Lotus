#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"

using namespace lotus;

Value lotus::ClassValue::sizeInRam() {
    return INT(sizeof(ClassValue));
}

MethodMemberInfo lotus::ClassValue::getMethod(const String& name, size_t argsCount) {
    if (methods.find(name) != methods.end()) {
        Ptr<MethodMemberInfo> variadic = nullptr;
        for (auto& method : methods[name]) {
            if (method.value.hasVariadic() && argsCount >= method.value.getArgsCount() - 1) variadic = MAKE_PTR<MethodMemberInfo>(method);
            if (method.value.getArgsCount() == argsCount) return method;
        }
        if (variadic) return *variadic;
        throw LotusException(STRING_LITERAL("No overload with ") + std::to_wstring(argsCount) +
            STRING_LITERAL(" arguments for method \"") + name + STRING_LITERAL("\""));
    }
    throw LotusException(STRING_LITERAL("Undefined method \"") + name + STRING_LITERAL("\""));
}

void lotus::ClassValue::constructor(const std::vector<Value>& args, Variables& variables) {
    if (methods.find(STRING_LITERAL("constructor")) != methods.end()) callMethod(STRING_LITERAL("constructor"), args, variables);
    else {
        for (auto& field : fields) {
            if (auto classField = std::dynamic_pointer_cast<ClassValue>(field.second.value)) {
                classField->constructor({}, variables);
            }
        }
    }
}

void lotus::ClassValue::declareField(const String& name, const FieldMemberInfo& memberInfo) {
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
    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value ClassValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    auto methodInfo = getMethod(name, args.size());
    if (methodInfo.accessModifier == AccessModifierType::PRIVATE) {
        throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
    }

    ClassValue thisValue = *this;
    for (auto& field : thisValue.fields) {
        field.second.accessModifier = AccessModifierType::PUBLIC;
    }
    for (auto& methodVector : thisValue.methods) {
        for (auto& method : methodVector.second) {
            method.accessModifier = AccessModifierType::PUBLIC;
        }
    }

    variables.declare(STRING_LITERAL("this"), MAKE_PTR<ClassValue>(thisValue));
    Value returnValue = methodInfo.value.call(args, variables);

    if (auto thisValueAfterMethod = std::dynamic_pointer_cast<ClassValue>(variables.get(STRING_LITERAL("this")))) {
        if (fields.size() != thisValueAfterMethod->fields.size()) {
            throw LotusException(STRING_LITERAL("Different size of thisValue before and after method"));
        }
        for (auto& field : fields) {
            auto find = thisValueAfterMethod->fields.find(field.first);
            if (find == thisValueAfterMethod->fields.end()) {
                throw LotusException(STRING_LITERAL("Elements of thisValue before and after calling method are different"));
            }
            field.second.value = find->second.value;
        }
    }

    variables.variables.erase(STRING_LITERAL("this"));
    return returnValue;
}
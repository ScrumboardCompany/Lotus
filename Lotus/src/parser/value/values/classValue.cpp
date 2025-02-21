#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "parser/value/lambdaValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"

using namespace lotus;

void lotus::ClassValue::collectInheritedMembers(ClassValue& thisValue) {
    for (auto& parent : parents) {
        parent.collectInheritedMembers(thisValue);

        for (const auto& field : parent.fields) {
            if (field.second.accessModifier == AccessModifierType::PUBLIC ||
                field.second.accessModifier == AccessModifierType::PROTECTED) {
                thisValue.declareField(field.first, field.second);
            }
        }

        for (auto& method : parent.methods) {
            for (auto& overload : method.second) {
                if (overload.accessModifier == AccessModifierType::PUBLIC ||
                    overload.accessModifier == AccessModifierType::PROTECTED) {
                    thisValue.declareMethod(method.first, overload);
                }
            }
        }
    }
}

bool lotus::ClassValue::hasField(const String& name) {
    for (auto& parent : parents) {
        if (parent.hasField(name)) return true;

        return fields.find(name) != fields.end();
    }
    return fields.find(name) != fields.end();
}

bool lotus::ClassValue::assignField(const String& name, const FieldMemberInfo& field) {
    for (auto& parent : parents) {
        if (parent.assignField(name, field)) return true;

        if (fields.find(name) != fields.end()) {
            fields[name].value = field.value;
            return true;
        }
        else return false;
    }
    if (fields.find(name) != fields.end()) {
        fields[name].value = field.value;
        return true;
    }
    else return false;
}

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
    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value ClassValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    if (fields.find(name) != fields.end()) {
        if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(getField(name))) {
            if (lambda->getArgsCount() == args.size()) return getField(name)->call(args, variables);
        }
    }

    auto methodInfo = getMethod(name, args.size());
    if (methodInfo.accessModifier == AccessModifierType::PRIVATE) {
        throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
    }

    ClassValue thisValue;
    thisValue.fields = fields;
    thisValue.methods = methods;
    thisValue.type = getType();

    collectInheritedMembers(thisValue);

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

        for (auto& field : thisValueAfterMethod->fields) {
            if (!assignField(field.first, field.second)) {
                //throw LotusException(STRING_LITERAL("Elements of thisValue before and after calling method are different"));
            }
        }
    }

    variables.exitScope();
    //variables.variables.erase(STRING_LITERAL("this"));
    return returnValue;
}
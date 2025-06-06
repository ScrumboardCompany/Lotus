#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "parser/value/lambdaValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/module.h"

using namespace lotus;

bool lotus::ClassValue::hasField(const String& name) {
    if (fields.find(name) != fields.end()) return true;

    for (auto& parent : parents) {
        if (parent->hasField(name)) return true;
    }
    return false;
}

void lotus::ClassValue::protectedToPublicInParents(StringMap<AccessModifierType>& accessModifiers) {
    for (auto& field : fields) {
        if (field.second.accessModifier == AccessModifierType::PROTECTED) {
            accessModifiers.emplace(field.first, AccessModifierType::PROTECTED);
            field.second.accessModifier = AccessModifierType::PUBLIC;
        }
    }

    for (auto& methodVector : methods) {

        for (size_t i = 0; i < methodVector.second.size(); ++i) { // methodVector.first + STRING_LITERAL("#") + std::to_wstring(i)
            auto& method = methodVector.second[i];

            if (method.accessModifier == AccessModifierType::PROTECTED) {
                accessModifiers.emplace(methodVector.first + STRING_LITERAL("#") + std::to_wstring(i), AccessModifierType::PROTECTED);
                method.accessModifier = AccessModifierType::PUBLIC;
            }
        }
    }

    for (auto& parent : parents) {
        parent->protectedToPublicInParents(accessModifiers);
    }
}

void lotus::ClassValue::publicToProtectedInParents(const StringMap<AccessModifierType>& accessModifiers, bool needThis) {

    if (needThis) {
        for (auto& field : fields) {

            auto it = accessModifiers.find(field.first);
            if (it != accessModifiers.end()) {
                field.second.accessModifier = it->second;
            }
        }

        for (auto& methodVector : methods) {
            for (size_t i = 0; i < methodVector.second.size(); ++i) {
                auto& method = methodVector.second[i];

                auto it = accessModifiers.find(methodVector.first + STRING_LITERAL("#") + std::to_wstring(i));
                if (it != accessModifiers.end()) {
                    method.accessModifier = it->second;
                }
            }
        }
    }

    for (auto& parent : parents) {
        parent->publicToProtectedInParents(accessModifiers);
    }
}

void lotus::ClassValue::calculateSizeInRam(Int& size) {
    size += static_cast<Int>(sizeof(fields));

    for (auto& parent : parents) {
        parent->calculateSizeInRam(size);
    }
}

Int lotus::ClassValue::asInt(Module& module) {
    return callMethod(STRING_LITERAL("__asInt__"), {}, module)->asInt(module);
}

double lotus::ClassValue::asDouble(Module& module) {
    return callMethod(STRING_LITERAL("__asFloat__"), {}, module)->asDouble(module);
}

bool lotus::ClassValue::asBool(Module& module) {
    return callMethod(STRING_LITERAL("__asBool__"), {}, module)->asBool(module);
}

String lotus::ClassValue::asString(Module& module) {
    return callMethod(STRING_LITERAL("__asString__"), {}, module)->asString(module);
}

Value lotus::ClassValue::add(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__add__"), { other }, module);
}

Value lotus::ClassValue::substract(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__substract__"), { other }, module);
}

Value lotus::ClassValue::multiply(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__multiply__"), { other }, module);
}

Value lotus::ClassValue::divide(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__divide__"), { other }, module);
}

Value lotus::ClassValue::power(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__power__"), { other }, module);
}

Value lotus::ClassValue::divideModule(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__divideModule__"), { other }, module);
}

Value lotus::ClassValue::bitwiseAnd(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseAnd__"), { other }, module);
}

Value lotus::ClassValue::bitwiseOr(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseOr__"), { other }, module);
}

Value lotus::ClassValue::bitwiseXor(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseXor__"), { other }, module);
}

Value lotus::ClassValue::bitwiseNot(Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseNot__"), {}, module);
}

Value lotus::ClassValue::bitwiseLeftShift(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseLeftShift__"), { other }, module);
}

Value lotus::ClassValue::bitwiseRightShift(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseRightShift__"), { other }, module);
}

Value lotus::ClassValue::greater(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__greater__"), { other }, module);
}

Value lotus::ClassValue::less(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__less__"), { other }, module);
}

Value lotus::ClassValue::greaterEqual(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__greaterEqual__"), { other }, module);
}

Value lotus::ClassValue::lessEqual(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__lessEqual__"), { other }, module);
}

Value lotus::ClassValue::equality(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__equality__"), { other }, module);
}

Value lotus::ClassValue::inequality(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__inequality__"), { other }, module);
}

Value lotus::ClassValue::logicalOr(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__logicalOr__"), { other }, module);
}

Value lotus::ClassValue::logicalAnd(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__logicalAnd__"), { other }, module);
}

Value lotus::ClassValue::addSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__addSet__"), { other }, module);
}

Value lotus::ClassValue::substractSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__substractSet__"), { other }, module);
}

Value lotus::ClassValue::multiplySet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__multiplySet__"), { other }, module);
}

Value lotus::ClassValue::divideSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__divideSet__"), { other }, module);
}

Value lotus::ClassValue::powerSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__powerSet__"), { other }, module);
}

Value lotus::ClassValue::divideModuleSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__divideModuleSet__"), { other }, module);
}

Value lotus::ClassValue::bitwiseAndSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseAndSet__"), { other }, module);
}

Value lotus::ClassValue::bitwiseOrSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseOrSet__"), { other }, module);
}

Value lotus::ClassValue::bitwiseXorSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseXorSet__"), { other }, module);
}

Value lotus::ClassValue::bitwiseNotSet(Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseNotSet__"), {}, module);
}

Value lotus::ClassValue::bitwiseLeftShiftSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseLeftShiftSet__"), { other }, module);
}

Value lotus::ClassValue::bitwiseRightShiftSet(const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__bitwiseRightShiftSet__"), { other }, module);
}

Value lotus::ClassValue::unaryPlus(Module& module) {
    return callMethod(STRING_LITERAL("__unaryPlus__"), {}, module);
}

Value lotus::ClassValue::unaryMinus(Module& module) {
    return callMethod(STRING_LITERAL("__unaryMinus__"), {}, module);
}

Value lotus::ClassValue::unaryNot(Module& module) {
    return callMethod(STRING_LITERAL("__unaryNot__"), {}, module);
}

Value lotus::ClassValue::prefixIncrement(Module& module) {
    return callMethod(STRING_LITERAL("__prefixIncrement__"), {}, module);
}

Value lotus::ClassValue::postfixIncrement(Module& module) {
    return callMethod(STRING_LITERAL("__postfixIncrement__"), {}, module);
}

Value lotus::ClassValue::prefixDecrement(Module& module) {
    return callMethod(STRING_LITERAL("__prefixDecrement__"), {}, module);
}

Value lotus::ClassValue::postfixDecrement(Module& module) {
    return callMethod(STRING_LITERAL("__postfixDecrement__"), {}, module);
}

Value lotus::ClassValue::size(Module& module) {
    return callMethod(STRING_LITERAL("__size__"), {}, module);
}

Value lotus::ClassValue::getOfIndex(const Value& index, Module& module) {
    return callMethod(STRING_LITERAL("__getOfIndex__"), {index}, module);
}

Value lotus::ClassValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    return callMethod(STRING_LITERAL("__setOfIndex__"), { index, other }, module);
}

Value lotus::ClassValue::sizeInRam() {
    Int size = 0;
    calculateSizeInRam(size);
    return INT(size);
}

ClassValue& lotus::ClassValue::getMethod(const String& name, size_t argsCount, MethodMemberInfo& memberInfo, Ptr<FieldMemberInfo> field) {
    if (methods.find(name) != methods.end()) {
        Ptr<MethodMemberInfo> variadic = nullptr;
        for (auto& method : methods[name]) {
            if (method.value.hasVariadic() && argsCount >= method.value.getArgsCount() - 1)
                variadic = MAKE_PTR<MethodMemberInfo>(method);
            if (method.value.getArgsCount() == argsCount) {
                memberInfo = method;
                return *this;
            }
        }
        if (variadic) {
            memberInfo = *variadic;
            return *this;
        }
    }

    for (auto& parent : parents) {
        try {
            MethodMemberInfo parentMemberInfo;
            ClassValue& parentClass = parent->getMethod(name, argsCount, parentMemberInfo, field);
            memberInfo = parentMemberInfo;
            return parentClass;
        }
        catch (const LotusException&) {
            continue;
        }
    }

    if (fields.find(name) != fields.end()) {
        field->value = fields[name].value;
        return *this;
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
        else if (fields[name].accessModifier == AccessModifierType::PROTECTED) {
            throw LotusException(STRING_LITERAL("Request to protected field: \"") + name + STRING_LITERAL("\""));
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

Value ClassValue::callMethod(const String& name, const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs) {
    MethodMemberInfo methodInfo;
    Ptr<FieldMemberInfo> field = MAKE_PTR<FieldMemberInfo>();
    ClassValue& value = getMethod(name, args.size() + specifiedArgs.size(), methodInfo, field);
    bool isParentClass = value.getType() != getType();

    if (field->value) {
        if (field->accessModifier == AccessModifierType::PRIVATE) {
            throw LotusException(STRING_LITERAL("Request to private field: \"") + name + STRING_LITERAL("\""));
        }
        else if (field->accessModifier == AccessModifierType::PROTECTED) {
            throw LotusException(STRING_LITERAL("Request to protected field: \"") + name + STRING_LITERAL("\""));
        }

        return field->value->call(args, module, specifiedArgs);
    }

    if (methodInfo.accessModifier == AccessModifierType::PRIVATE) {
        throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
    }
    else if (methodInfo.accessModifier == AccessModifierType::PROTECTED) {
        throw LotusException(STRING_LITERAL("Request to protected method: \"") + name + STRING_LITERAL("\""));
    }

    ClassValue thisValue;
    thisValue.fields = value.fields;
    thisValue.methods = value.methods;
    thisValue.parents = value.parents;
    thisValue.type = value.getType();

    StringMap<AccessModifierType> accessModifiers;

    for (auto& field : thisValue.fields) {
        accessModifiers.emplace(field.first, field.second.accessModifier);

        if (!isParentClass || (field.second.accessModifier != AccessModifierType::PRIVATE))
            field.second.accessModifier = AccessModifierType::PUBLIC;
    }
    for (auto& methodVector : thisValue.methods) {
        
        for (size_t i = 0; i < methodVector.second.size(); ++i) {
            auto& method = methodVector.second[i];

            accessModifiers.emplace(methodVector.first + STRING_LITERAL("#") + std::to_wstring(i), method.accessModifier);

            if (!isParentClass || (method.accessModifier != AccessModifierType::PRIVATE))
                method.accessModifier = AccessModifierType::PUBLIC;
        }
    }

    protectedToPublicInParents(accessModifiers);

    module.variables.enterScope();
    module.variables.declare(STRING_LITERAL("this"), MAKE_PTR<ClassValue>(thisValue));
    Value returnValue = methodInfo.value.call(args, specifiedArgs, module);

    if (auto thisValueAfterMethod = std::dynamic_pointer_cast<ClassValue>(module.variables.get(STRING_LITERAL("this")))) {

        value.fields = thisValueAfterMethod->fields;
        value.methods = thisValueAfterMethod->methods;
        value.parents = thisValueAfterMethod->parents;
    }

    for (auto& field : value.fields) {

        auto it = accessModifiers.find(field.first);
        if (it != accessModifiers.end()) {
            field.second.accessModifier = it->second;
        }
    }

    for (auto& methodVector : value.methods) {
        for (size_t i = 0; i < methodVector.second.size(); ++i) {
            auto& method = methodVector.second[i];

            auto it = accessModifiers.find(methodVector.first + STRING_LITERAL("#") + std::to_wstring(i));
            if (it != accessModifiers.end()) {
                method.accessModifier = it->second;
            }
        }
    }
    
    publicToProtectedInParents(accessModifiers, false);

    module.variables.exitScope();
    return returnValue;
}

Value lotus::ClassValue::call(const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs) {
    return callMethod(STRING_LITERAL("__call__"), args, module, specifiedArgs);
}
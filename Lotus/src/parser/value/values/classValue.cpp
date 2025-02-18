#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"

using namespace lotus;

Value lotus::ClassValue::sizeInRam() {
    return INT(sizeof(ClassValue));
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

Value& lotus::ClassValue::getField(const String& name) {
    if (fields.find(name) != fields.end()) {
        if (fields[name].accessModifier == AccessModifierType::PRIVATE) {
            throw LotusException(STRING_LITERAL("Request to private field: \"") + name + STRING_LITERAL("\""));
        }
        return fields[name].value;
    }
    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value lotus::ClassValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    if (methods.find(name) != methods.end()) {

        if (methods[name].accessModifier == AccessModifierType::PRIVATE) {
            throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
        }

        ClassValue thisValue;
        thisValue.fields = fields;
        thisValue.methods = methods;

        for (auto& field : thisValue.fields) {
            field.second.accessModifier = AccessModifierType::PUBLIC;
        }

        for (auto& method : thisValue.methods) {
            method.second.accessModifier = AccessModifierType::PUBLIC;
        }

        variables.declare(STRING_LITERAL("this"), MAKE_PTR<ClassValue>(thisValue));

        Value returnValue = methods[name].value.call(args, variables);

        if (auto thisValueAfterMethod = std::dynamic_pointer_cast<ClassValue>(variables.get(STRING_LITERAL("this")))) {if (fields.size() != thisValueAfterMethod->fields.size()) throw LotusException(STRING_LITERAL("Different size of thisValue before method and after method"));

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
    throw LotusException(STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" does not exist"));
}
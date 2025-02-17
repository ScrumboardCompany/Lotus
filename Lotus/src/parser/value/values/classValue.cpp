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
            if (auto classField = std::dynamic_pointer_cast<ClassValue>(field.second)) {
                classField->constructor({}, variables);
            }
        }
    }
}

Value& lotus::ClassValue::getField(const String& name) {
    if (fields.find(name) != fields.end()) return fields[name];
    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value lotus::ClassValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    if (methods.find(name) != methods.end()) {

        ClassValue thisValue;
        thisValue.fields = fields;
        thisValue.methods = methods;

        variables.declare(STRING_LITERAL("this"), MAKE_PTR<ClassValue>(thisValue));

        Value returnValue = methods[name].call(args, variables);

        variables.variables.erase(STRING_LITERAL("this"));

        return returnValue;
    }
    throw LotusException(STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" does not exist"));
}
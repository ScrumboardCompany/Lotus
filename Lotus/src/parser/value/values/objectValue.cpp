#include "parser/value/objectValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "parser/statement/statement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/module.h"

using namespace lotus;

lotus::ObjectValue::ObjectValue(const StringMap<Value>& fields) : fields(fields) {
    type = STRING_LITERAL("object");
}

String lotus::ObjectValue::asString(Module& module) {
    String result = STRING_LITERAL("{\n");

    for (auto& el : fields) {
        result += STRING_LITERAL("\t") + el.first + STRING_LITERAL(" = ") + el.second->asString(module) + STRING_LITERAL(";\n");
    }

    result += STRING_LITERAL("}");
    return result;
}

Value lotus::ObjectValue::add(const Value& other, Module&) {
    if (other->getType() == STRING_LITERAL("object")) {
        StringMap<Value> newFields = fields;

        Ptr<ObjectValue> value = std::dynamic_pointer_cast<ObjectValue>(other);
        if (!value) {
            throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Dynamic cast to ObjectValue failed"));
        }

        for (auto& el : value->fields) {
            newFields.emplace(el.first, el.second);
        }

        return OBJECT(newFields);
    }
    throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
}

Value lotus::ObjectValue::addSet(const Value& other, Module& module) {
    if (auto arr = std::dynamic_pointer_cast<ObjectValue>(add(other, module))) {
        fields = arr->fields;
    }
    return OBJECT(fields);
}

Value& lotus::ObjectValue::getField(const String& name) {
    if (fields.find(name) != fields.end()) {
        return fields[name];
    }

    throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

void lotus::ObjectValue::foreach(const String& name, const Statement& body, Module& module) {
    for (auto& field : fields) {
        module.variables.set(name, field.second);
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

Value lotus::ObjectValue::getOfIndex(const Value& index, Module& module) {
    if (index->getType() == STRING_LITERAL("string")) return fields[index->asString(module)];
    throwOverloadError(STRING_LITERAL("index"), getType(), index->getType());
}

Value lotus::ObjectValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("string")) {
        fields[index->asString(module)] = other;
        return fields[index->asString(module)];
    };
    throwOverloadError(STRING_LITERAL("index"), getType(), index->getType());
}

Value lotus::ObjectValue::size(Module&) {
    return INT(static_cast<Int>(fields.size()));
}

Value lotus::ObjectValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::OBJECT(const StringMap<Value>& fields) {
    return MAKE_PTR<ObjectValue>(fields);
}
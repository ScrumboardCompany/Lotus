#include "parser/value/objectValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "parser/statement/statement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"

using namespace lotus;

lotus::ObjectValue::ObjectValue(const StringMap<Value>& fields) : fields(fields) {
    type = STRING_LITERAL("object");
}

String lotus::ObjectValue::asString() {
    String result = STRING_LITERAL("{\n");

    for (auto& el : fields) {
        result += STRING_LITERAL("\t") + el.first + STRING_LITERAL(" = ") + el.second->asString() + STRING_LITERAL(";\n");
    }

    result += STRING_LITERAL("}");
    return result;
}

Value lotus::ObjectValue::add(const Value& other) {
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

Value lotus::ObjectValue::addSet(const Value& other) {
    if (auto arr = std::dynamic_pointer_cast<ObjectValue>(add(other))) {
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

void lotus::ObjectValue::foreach(const String& name, const Statement& body, Variables& variables) {
    for (auto& field : fields) {
        variables.set(name, field.second);
        try {
            body->execute();
        }
        catch (const ContinueStatement&) {
            continue;
        }
        catch (const BreakStatement&) {
            break;
        }
    }
}

Value& lotus::ObjectValue::index(const Value& index) {
    if (index->getType() == STRING_LITERAL("string")) return fields[index->asString()];
    throwOverloadError(STRING_LITERAL("index"), getType(), index->getType());
}

Value lotus::ObjectValue::size() {
    return INT(fields.size());
}

Value lotus::ObjectValue::sizeInRam() {
    return INT(sizeof(ObjectValue));
}
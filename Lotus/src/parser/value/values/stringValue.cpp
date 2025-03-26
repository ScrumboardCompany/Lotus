#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "parser/value/arrayValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/module.h"
#include <algorithm>

using namespace lotus;

lotus::StringValue::StringValue(const char* value, Module& module) : StringValue(STRING_VAR_LITERAL(value), module) {}

StringValue::StringValue(const String& value, Module& module) : value(value) {
    type = STRING_LITERAL("string");

    declareMethod(STRING_LITERAL("size"), METHOD(AccessModifierType::PUBLIC, [&] {
        RETURN_VALUE(INT(this->value.size()));
        }));

    declareMethod(STRING_LITERAL("clear"), METHOD(AccessModifierType::PUBLIC, [&] {
        this->value.clear();
        }));

    declareMethod(STRING_LITERAL("isEmpty"), METHOD(AccessModifierType::PUBLIC, [&] {
        RETURN_VALUE(BOOL(this->value.empty()));
        }));

    declareMethod(STRING_LITERAL("substring"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("start")->instanceOf("int") || !module.GET("length")->instanceOf("int"))
            module.THROW(STRING("Start and length must be integers", module), STRING("type_error", module));
        Int start = module.GET("start")->asInt(module);
        Int length = module.GET("length")->asInt(module);
        if (start < 0 || length < 0 || start + length > this->value.size()) {
            module.THROW(STRING("Invalid substring range", module), STRING("out_of_range", module));
        }
        RETURN_VALUE(STRING(this->value.substr(start, length), module));
        }, "start", "length"));

    declareMethod(STRING_LITERAL("substring"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("length")->instanceOf("int"))
            module.THROW(STRING("Length must be integer", module), STRING("type_error", module));
        Int start = module.GET("start")->asInt(module);
        if (start < 0 || start > this->value.size()) {
            module.THROW(STRING("Invalid substring range", module), STRING("out_of_range", module));
        }
        RETURN_VALUE(STRING(this->value.substr(start), module));
        }, "start"));

    declareMethod(STRING_LITERAL("find"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("substring")->instanceOf("string"))
            module.THROW(STRING("Substring must be a string", module), STRING("type_error", module));
        String substring = module.GET("substring")->asString(module);
        RETURN_VALUE(INT(this->value.find(substring)));
        }, "substring"));

    declareMethod(STRING_LITERAL("findLast"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("substring")->instanceOf("string"))
            module.THROW(STRING("Substring must be a string", module), STRING("type_error", module));
        String substring = module.GET("substring")->asString(module);
        RETURN_VALUE(INT(this->value.rfind(substring)));
        }, "substring"));

    declareMethod(STRING_LITERAL("replace"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("old")->instanceOf("string") || !module.GET("new")->instanceOf("string"))
            module.THROW(STRING("Both old and new values must be strings", module), STRING("type_error", module));
        String oldStr = module.GET("old")->asString(module);
        String newStr = module.GET("new")->asString(module);
        size_t pos = 0;
        while ((pos = this->value.find(oldStr, pos)) != -1) {
            this->value.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
        RETURN_VALUE(STRING(this->value, module));
        }, "old", "new"));

    declareMethod(STRING_LITERAL("toUpper"), METHOD(AccessModifierType::PUBLIC, [&] {
        std::transform(this->value.begin(), this->value.end(), this->value.begin(), ::toupper);
        RETURN_VALUE(STRING(this->value, module));
        }));

    declareMethod(STRING_LITERAL("toLower"), METHOD(AccessModifierType::PUBLIC, [&] {
        std::transform(this->value.begin(), this->value.end(), this->value.begin(), ::tolower);
        RETURN_VALUE(STRING(this->value, module));
        }));

    declareMethod(STRING_LITERAL("trim"), METHOD(AccessModifierType::PUBLIC, [&] {
        this->value.erase(0, this->value.find_first_not_of(L" \t\n\r"));
        this->value.erase(this->value.find_last_not_of(L" \t\n\r") + 1);
        RETURN_VALUE(STRING(this->value, module));
        }));

    declareMethod(STRING_LITERAL("split"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("delimiter")->instanceOf("string"))
            module.THROW(STRING("Delimiter must be a string", module), STRING("type_error", module));
        String delimiter = module.GET("delimiter")->asString(module);
        if (delimiter.empty())
            RETURN_VALUE(ARRAY({ STRING(this->value, module) }, module));
        std::vector<Value> parts;
        size_t pos = 0, start = 0;
        while ((pos = this->value.find(delimiter, start)) != -1) {
            parts.push_back(STRING(this->value.substr(start, pos - start), module));
            start = pos + delimiter.length();
        }
        parts.push_back(STRING(this->value.substr(start), module));
        RETURN_VALUE(ARRAY(parts, module));
        }, "delimiter"));

    declareMethod(STRING_LITERAL("startsWith"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("prefix")->instanceOf("string"))
            module.THROW(STRING("Prefix must be a string", module), STRING("type_error", module));
        String prefix = module.GET("prefix")->asString(module);
        RETURN_VALUE(BOOL(this->value.find(prefix) == 0));
        }, "prefix"));

    declareMethod(STRING_LITERAL("endsWith"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("suffix")->instanceOf("string"))
            module.THROW(STRING("Suffix must be a string", module), STRING("type_error", module));
        String suffix = module.GET("suffix")->asString(module);
        RETURN_VALUE(BOOL(this->value.size() >= suffix.size() &&
            this->value.compare(this->value.size() - suffix.size(),
                suffix.size(), suffix) == 0));
        }, "suffix"));

    declareMethod(STRING_LITERAL("contains"), METHOD(AccessModifierType::PUBLIC, [&] {
        if (!module.GET("substring")->instanceOf("string"))
            module.THROW(STRING("Substring must be a string", module), STRING("type_error", module));
        String substring = module.GET("substring")->asString(module);
        RETURN_VALUE(BOOL(this->value.find(substring) != -1));
        }, "substring"));

    declareMethod(STRING_LITERAL("reverse"), METHOD(AccessModifierType::PUBLIC, [&] {
        std::reverse(this->value.begin(), this->value.end());
        RETURN_VALUE(STRING(this->value, module));
        }));
}

Int lotus::StringValue::asInt(Module&) {
    return std::stoll(value);
}

double lotus::StringValue::asDouble(Module&) {
    return std::stod(value);
}

bool lotus::StringValue::asBool(Module&) {
    return value.length() != 0;
}

String lotus::StringValue::asString(Module&) {
    return value;
}

Value lotus::StringValue::add(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
    return STRING(value + other->asString(module), module);
}

Value lotus::StringValue::multiply(const Value& other, Module& module) {
    if (!other->instanceOf("string") && !other->instanceOf("int")) throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (Int i = 0; i < other->asInt(module); i++) {
            result += value;
        }
        return STRING(result, module);
    }
    throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
}

Value lotus::StringValue::greater(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("greater"), getType(), other->getType());
    return BOOL(value > other->asString(module));
}

Value lotus::StringValue::less(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("less"), getType(), other->getType());
    return BOOL(value < other->asString(module));
}

Value lotus::StringValue::greaterEqual(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("greaterEqual"), getType(), other->getType());
    return BOOL(value >= other->asString(module));
}

Value lotus::StringValue::lessEqual(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("lessEqual"), getType(), other->getType());
    return BOOL(value <= other->asString(module));
}

Value lotus::StringValue::equality(const Value& other, Module& module) {
    return BOOL(value == other->asString(module));
}

Value lotus::StringValue::inequality(const Value& other, Module& module) {
    return BOOL(value != other->asString(module));
}

Value lotus::StringValue::logicalOr(const Value& other, Module& module) {
    return BOOL(asBool(module) || other->asBool(module));
}

Value lotus::StringValue::logicalAnd(const Value& other, Module& module) {
    return BOOL(asBool(module) && other->asBool(module));
}

Value lotus::StringValue::addSet(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("addSet"), getType(), other->getType());
    value = add(other, module)->asString(module);
    return STRING(value, module);
}

Value lotus::StringValue::multiplySet(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("multiplySet"), getType(), other->getType());
    value = multiply(other, module)->asString(module);
    return STRING(value, module);
}

Value lotus::StringValue::getOfIndex(const Value& index, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        return STRING(String(1, value[static_cast<int>(index->asInt(module))]), module);
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        String otherAsString = other->asString(module);
        if (otherAsString.empty()) {
            value[static_cast<int>(index->asInt(module))] = '\0';
        } else {
            value[static_cast<int>(index->asInt(module))] = otherAsString[0];
        }
        return STRING(String(1, value[static_cast<int>(index->asInt(module))]), module);
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::size(Module&) {
    return INT(static_cast<Int>(value.size()));
}

Value lotus::StringValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::STRING(const char* value, Module& module) {
    return STRING(STRING_VAR_LITERAL(value), module);
}

Value lotus::STRING(const String& value, Module& module) {
    return MAKE_PTR<StringValue>(value, module);
}

Value lotus::STRING() {
    return MAKE_PTR<StringValue>();
}
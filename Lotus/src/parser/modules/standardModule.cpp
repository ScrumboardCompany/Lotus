#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/intValue.h"
#include "parser/value/boolValue.h"
#include <iostream>
#include <random>
#include "utils/utils.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Parser::loadStandardModule() {
	module.DEF("throw", [](Module& module) {
		module.THROW();
		});

	module.DEF("throw", [](Module& module) {
		module.THROW(module.GET("msg"));
		}, "msg");

	module.DEF("throw", [](Module& module) {
		module.THROW(module.GET("msg"), module.GET("type"));
		}, "msg", "type");

	module.DEF("print", [](Module& module) {
		Value args = module.GET("args");
		for (Int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module);
		}
		}, "args...");

	module.DEF("println", [](Module& module) {
		Value args = module.GET("args");
		for (Int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module) << std::endl;
		}
		}, "args...");

	module.DEF("input", [](Module& module) {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input));
		});

	module.DEF("rand", [](Module& module) {
		if (!module.GET("min")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("min")->getType(), module);
		if (!module.GET("max")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("max")->getType(), module);

		if (module.GET("min")->asInt(module) > module.GET("max")->asInt(module)) {
			Value temp = module.GET("min");
			module.GET("min") = module.GET("max");
			module.GET("max") = temp;
		}

		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<Int> distrib(module.GET("min")->asInt(module), module.GET("max")->asInt(module));

		RETURN_VALUE(INT(distrib(gen)));
		}, "min", "max");

	module.DEF("rand", [](Module& module) {
		RETURN_VALUE(module.CALL("rand", INT(0ll), module.GET("max")));
		}, "max");

	module.DEF("typeof", [](Module& module) {
		RETURN_VALUE(STRING(module.GET("value")->getType()));
		}, "value");

	module.DEF("size", [](Module& module) {
		RETURN_VALUE(module.GET("value")->size(module));
		}, "value");

	module.DEF("sizeof", [](Module& module) {
		RETURN_VALUE(module.GET("value")->sizeInRam());
		}, "value");

	module.DEF("int", [](Module& module) {
		RETURN_VALUE(INT(module.GET("value")->asInt(module)));
		}, "value");

	module.DEF("float", [](Module& module) {
		RETURN_VALUE(FLOAT(module.GET("value")->asDouble(module)));
		}, "value");

	module.DEF("string", [](Module& module) {
		RETURN_VALUE(STRING(module.GET("value")->asString(module)));
		}, "value");

	module.DEF("bool", [](Module& module) {
		RETURN_VALUE(BOOL(module.GET("value")->asBool(module)));
		}, "value");

	Class exceptionClass;

	exceptionClass.addField("__msg", FIELD(AccessModifierType::PRIVATE, STRING("error")));
	exceptionClass.addField("__type", FIELD(AccessModifierType::PRIVATE, STRING("error")));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [](Module& module) {}));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		module.GET("this")->getField("__msg") = module.GET("msg");
		}, "msg"));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		module.GET("this")->getField("__msg") = module.GET("msg");
		module.GET("this")->getField("__type") = module.GET("type");
		}, "msg", "type"));

	exceptionClass.addMethod("message", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		RETURN_VALUE(module.GET("this")->getField("__msg"));
		}));

	exceptionClass.addMethod("type", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		RETURN_VALUE(module.GET("this")->getField("__type"));
		}));

	Static stringStatic;

	stringStatic.addMethod(STRING_LITERAL("replace"), METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		if (!module.GET("old")->instanceOf("string") || !module.GET("new")->instanceOf("string"))
			module.THROW(STRING("Both old and new values must be strings"), STRING("type_error"));
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string"), STRING("type_error"));
		String oldStr = module.GET("old")->asString(module);
		String newStr = module.GET("new")->asString(module);
		String value = module.GET("value")->asString(module);
		size_t pos = 0;
		while ((pos = value.find(oldStr, pos)) != String::npos) {
			value.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
		RETURN_VALUE(STRING(value));
		}, "value", "old", "new"));

	stringStatic.addMethod(STRING_LITERAL("toUpper"), METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string"), STRING("type_error"));
		String value = module.GET("value")->asString(module);
		std::transform(value.begin(), value.end(), value.begin(), ::toupper);
		RETURN_VALUE(STRING(value));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("toLower"), METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string"), STRING("type_error"));
		String value = module.GET("value")->asString(module);
		std::transform(value.begin(), value.end(),value.begin(), ::tolower);
		RETURN_VALUE(STRING(value));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("trim"), METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string"), STRING("type_error"));
		String value = module.GET("value")->asString(module);
		value.erase(0, value.find_first_not_of(L" \t\n\r"));
		value.erase(value.find_last_not_of(L" \t\n\r") + 1);
		RETURN_VALUE(STRING(value));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("reverse"), METHOD(AccessModifierType::PUBLIC, [](Module& module) {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string"), STRING("type_error"));
		String value = module.GET("value")->asString(module);
		std::reverse(value.begin(), value.end());
		RETURN_VALUE(STRING(value));
		}, "value"));

	module.CLASS("exception", exceptionClass);
	module.STATIC("string", stringStatic);
}
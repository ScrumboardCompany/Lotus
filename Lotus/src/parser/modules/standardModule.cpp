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
	module.DEF("throw", [&] {
		module.THROW();
		});

	module.DEF("throw", [&] {
		module.THROW(module.GET("msg"));
		}, "msg");

	module.DEF("throw", [&] {
		module.THROW(module.GET("msg"), module.GET("type"));
		}, "msg", "type");

	module.DEF("print", [&] {
		Value args = module.GET("args");
		for (Int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module);
		}
		}, "args...");

	module.DEF("println", [&] {
		Value args = module.GET("args");
		for (Int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module) << std::endl;
		}
		}, "args...");

	module.DEF("input", [&] {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input, module));
		});

	module.DEF("rand", [&] {
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

	module.DEF("rand", [&] {
		RETURN_VALUE(module.CALL("rand", INT(0ll), module.GET("max")));
		}, "max");

	module.DEF("typeof", [&] {
		RETURN_VALUE(STRING(module.GET("value")->getType(), module));
		}, "value");

	module.DEF("size", [&] {
		RETURN_VALUE(module.GET("value")->size(module));
		}, "value");

	module.DEF("sizeof", [&] {
		RETURN_VALUE(module.GET("value")->sizeInRam());
		}, "value");

	module.DEF("int", [&] {
		RETURN_VALUE(INT(module.GET("value")->asInt(module)));
		}, "value");

	module.DEF("float", [&] {
		RETURN_VALUE(FLOAT(module.GET("value")->asDouble(module)));
		}, "value");

	module.DEF("string", [&] {
		RETURN_VALUE(STRING(module.GET("value")->asString(module), module));
		}, "value");

	module.DEF("bool", [&] {
		RETURN_VALUE(BOOL(module.GET("value")->asBool(module)));
		}, "value");

	Class exceptionClass;

	exceptionClass.addField("__msg", FIELD(AccessModifierType::PRIVATE, STRING("error", module)));
	exceptionClass.addField("__type", FIELD(AccessModifierType::PRIVATE, STRING("error", module)));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {}));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {
		module.GET("this")->getField("__msg") = module.GET("msg");
		}, "msg"));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {
		module.GET("this")->getField("__msg") = module.GET("msg");
		module.GET("this")->getField("__type") = module.GET("type");
		}, "msg", "type"));

	exceptionClass.addMethod("message", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("__msg"));
		}));

	exceptionClass.addMethod("type", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("__type"));
		}));

	Static stringStatic;

	stringStatic.addMethod(STRING_LITERAL("replace"), METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("old")->instanceOf("string") || !module.GET("new")->instanceOf("string"))
			module.THROW(STRING("Both old and new values must be strings", module), STRING("type_error", module));
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string", module), STRING("type_error", module));
		String oldStr = module.GET("old")->asString(module);
		String newStr = module.GET("new")->asString(module);
		String value = module.GET("value")->asString(module);
		size_t pos = 0;
		while ((pos = value.find(oldStr, pos)) != String::npos) {
			value.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
		RETURN_VALUE(STRING(value, module));
		}, "value", "old", "new"));

	stringStatic.addMethod(STRING_LITERAL("toUpper"), METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string", module), STRING("type_error", module));
		String value = module.GET("value")->asString(module);
		std::transform(value.begin(), value.end(), value.begin(), ::toupper);
		RETURN_VALUE(STRING(value, module));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("toLower"), METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string", module), STRING("type_error", module));
		String value = module.GET("value")->asString(module);
		std::transform(value.begin(), value.end(),value.begin(), ::tolower);
		RETURN_VALUE(STRING(value, module));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("trim"), METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string", module), STRING("type_error", module));
		String value = module.GET("value")->asString(module);
		value.erase(0, value.find_first_not_of(L" \t\n\r"));
		value.erase(value.find_last_not_of(L" \t\n\r") + 1);
		RETURN_VALUE(STRING(value, module));
		}, "value"));

	stringStatic.addMethod(STRING_LITERAL("reverse"), METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("value")->instanceOf("string"))
			module.THROW(STRING("Value must be a string", module), STRING("type_error", module));
		String value = module.GET("value")->asString(module);
		std::reverse(value.begin(), value.end());
		RETURN_VALUE(STRING(value, module));
		}, "value"));

	module.CLASS("exception", exceptionClass, module);
	module.STATIC("string", stringStatic);
}
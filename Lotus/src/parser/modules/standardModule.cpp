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
		RETURN_VALUE(STRING(input));
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
		RETURN_VALUE(STRING(module.GET("value")->getType()));
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
		RETURN_VALUE(STRING(module.GET("value")->asString(module)));
		}, "value");

	module.DEF("bool", [&] {
		RETURN_VALUE(BOOL(module.GET("value")->asBool(module)));
		}, "value");

	Class exceptionClass;

	exceptionClass.addField("__msg", FIELD(AccessModifierType::PRIVATE, STRING("error")));
	exceptionClass.addField("__type", FIELD(AccessModifierType::PRIVATE, STRING("error")));

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

	module.CLASS("exception", exceptionClass, module, true);
}
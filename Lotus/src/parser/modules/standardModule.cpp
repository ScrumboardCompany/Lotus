#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/intValue.h"
#include "parser/value/boolValue.h"
#include <iostream>
#include "utils/utils.h"

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
		for (int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module);
		}
		}, "args...");

	module.DEF("println", [&] {
		Value args = module.GET("args");
		for (int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module) << std::endl;
		}
		}, "args...");

	module.DEF("input", [&] {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input));
		});

	module.DEF("typeof", [&] {
		RETURN_VALUE(STRING(module.GET("arg")->getType()));
		}, "arg");

	module.DEF("size", [&] {
		RETURN_VALUE(module.GET("arg")->size(module));
		}, "arg");

	module.DEF("sizeof", [&] {
		RETURN_VALUE(module.GET("arg")->sizeInRam());
		}, "arg");

	module.DEF("int", [&] {
		RETURN_VALUE(INT(module.GET("arg")->asInt(module)));
		}, "arg");

	module.DEF("float", [&] {
		RETURN_VALUE(FLOAT(module.GET("arg")->asDouble(module)));
		}, "arg");

	module.DEF("string", [&] {
		RETURN_VALUE(STRING(module.GET("arg")->asString(module)));
		}, "arg");

	module.DEF("bool", [&] {
		RETURN_VALUE(BOOL(module.GET("arg")->asBool(module)));
		}, "arg");

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
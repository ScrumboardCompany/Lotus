#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include <iostream>

void lotus::Parser::loadModules() {
	module.DEF("print", {
		std::wcout << module.variables.get("arg")->asString();
		}, "arg");

	module.DEF("input", {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input));
		});

	module.DEF("typeof", {
		RETURN_VALUE(STRING(module.variables.get("arg")->getType()));
		}, "arg");

	module.DEF("size", {
		RETURN_VALUE(module.variables.get("arg")->size());
		}, "arg");

	module.DEF("sizeof", {
		RETURN_VALUE(module.variables.get("arg")->sizeInRam());
		}, "arg");

	module.DEF("int", {
		RETURN_VALUE(INT(module.variables.get("arg")->asInt()));
		}, "arg");

	module.DEF("float", {
		RETURN_VALUE(FLOAT(module.variables.get("arg")->asDouble()));
		}, "arg");

	module.DEF("string", {
		RETURN_VALUE(STRING(module.variables.get("arg")->asString()));
		}, "arg");

	module.DEF("bool", {
		RETURN_VALUE(BOOL(module.variables.get("arg")->asBool()));
		}, "arg");

	Static popaStatic;

	popaStatic.addField("PI", FieldMemberInfo(FLOAT(3.14342354), AccessModifierType::PUBLIC));

	popaStatic.addMethod("GetPi", MethodMemberInfo(MAKE_CPP_FUNCTION({
		RETURN_VALUE(module.statics.get("Math").getField("PI"));
		}), AccessModifierType::PUBLIC));

	module.STATIC("Math", popaStatic);
}
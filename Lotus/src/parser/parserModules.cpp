#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include <iostream>

void lotus::Parser::loadModules() {
	module.DEF("print", [](Variables& variables) {
		std::wcout << variables.get("arg")->asString();
		}, "arg");

	module.DEF("input", [](Variables& variables) {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input));
		});

	module.DEF("typeof", [](Variables& variables) {
		RETURN_VALUE(STRING(variables.get("arg")->getType()));
		}, "arg");

	module.DEF("size", [](Variables& variables) {
		RETURN_VALUE(variables.get("arg")->size());
		}, "arg");

	module.DEF("int", [](Variables& variables) {
		RETURN_VALUE(INT(variables.get("arg")->asInt()));
		}, "arg");

	module.DEF("float", [](Variables& variables) {
		RETURN_VALUE(FLOAT(variables.get("arg")->asDouble()));
		}, "arg");

	module.DEF("string", [](Variables& variables) {
		RETURN_VALUE(STRING(variables.get("arg")->asString()));
		}, "arg");

	module.DEF("bool", [](Variables& variables) {
		RETURN_VALUE(BOOL(variables.get("arg")->asBool()));
		}, "arg");
}
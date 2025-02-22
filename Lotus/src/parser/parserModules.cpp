#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "structures/variables.h"
#include <iostream>
#include <thread>
#include <string>
#include <locale>
#include <codecvt>

void lotus::Parser::loadModules() {

	module.DEF("print", {
		Value args = module.variables.get("args");
		for (int i = 0, size = args->size()->asInt(); i < size; i++) {
			std::wcout << args->index(INT(i))->asString();
		}
		}, "args...");

	module.DEF("println", {
		Value args = module.variables.get("args");
		for (int i = 0, size = args->size()->asInt(); i < size; i++) {
			std::wcout << args->index(INT(i))->asString() << std::endl;
		}
		}, "args...");

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

	loadMathModule();
	loadTimeModule();
}

void lotus::Parser::loadMathModule() {
	Module Math;
	Static MathStatic;

	MathStatic.addField("PI", FieldMemberInfo(FLOAT(3.14342354), AccessModifierType::PUBLIC));
	MathStatic.addField("E", FieldMemberInfo(FLOAT(2.7182818284), AccessModifierType::PUBLIC));

	MathStatic.addMethod("absolute", MethodMemberInfo(MAKE_CPP_FUNCTION({
		if (module.variables.get("arg")->getType() == STRING_LITERAL("int")) RETURN_VALUE(INT(std::abs(module.variables.get("arg")->asInt())));
		RETURN_VALUE(FLOAT(std::abs(module.variables.get("arg")->asDouble())));
		}, "arg"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("round", MethodMemberInfo(MAKE_CPP_FUNCTION({
		RETURN_VALUE(INT(module.variables.get("arg")->asInt()));
		}, "arg"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("min", MethodMemberInfo(MAKE_CPP_FUNCTION({
		RETURN_VALUE(FLOAT(std::min(module.variables.get("arg1")->asDouble(), module.variables.get("arg2")->asDouble())));
		}, "arg1", "arg2"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("max", MethodMemberInfo(MAKE_CPP_FUNCTION({
		RETURN_VALUE(FLOAT(std::max(module.variables.get("arg1")->asDouble(), module.variables.get("arg2")->asDouble())));
		}, "arg1", "arg2"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("sqrt", MethodMemberInfo(MAKE_CPP_FUNCTION({
		RETURN_VALUE(FLOAT(std::sqrt(module.variables.get("arg")->asDouble())));
		}, "arg"), AccessModifierType::PUBLIC));

	Math.STATIC("Math", MathStatic);
	modules.emplace(STRING_LITERAL("Math"), Math);
}

void lotus::Parser::loadTimeModule() {
	Module Time;
	Static TimeStatic;

	TimeStatic.addMethod("sleep", MethodMemberInfo(MAKE_CPP_FUNCTION({
		std::this_thread::sleep_for(std::chrono::milliseconds(module.variables.get("duration")->asInt()));
		}, "duration"), AccessModifierType::PUBLIC));

	Time.STATIC("Time", TimeStatic);
	modules.emplace(STRING_LITERAL("Time"), Time);
}
#include "parser/parser.h"
#include "parser/value/floatValue.h"
#include "parser/value/intValue.h"
#include <cmath>

using namespace lotus;

void lotus::Parser::loadMathModule() {
	Module Math;

	Math.DEF("absolute", [&] {
		if (module.GET("arg")->getType() == STRING_LITERAL("int")) RETURN_VALUE(INT(std::abs(module.GET("arg")->asInt(module))));
		RETURN_VALUE(FLOAT(std::abs(module.GET("arg")->asDouble(module))));
		}, "arg");

	Math.DEF("round", [&] {
		RETURN_VALUE(INT(module.GET("arg")->asInt(module)));
		}, "arg");

	Math.DEF("min", [&] {
		RETURN_VALUE(FLOAT(std::min(module.GET("arg1")->asDouble(module), module.GET("arg2")->asDouble(module))));
		}, "arg1", "arg2");

	Math.DEF("max", [&] {
		RETURN_VALUE(FLOAT(std::max(module.GET("arg1")->asDouble(module), module.GET("arg2")->asDouble(module))));
		}, "arg1", "arg2");

	Math.DEF("sqrt", [&] {
		RETURN_VALUE(FLOAT(std::sqrt(module.GET("arg")->asDouble(module))));
		}, "arg");

	Math.DEF("PI", [&] {
		RETURN_VALUE(FLOAT(3.14342354));
		});

	Math.DEF("E", [&] {
		RETURN_VALUE(FLOAT(2.7182818284));
		});

	modules.emplace(STRING_LITERAL("Math"), Math);
}
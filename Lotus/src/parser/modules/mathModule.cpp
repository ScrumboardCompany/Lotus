#include "parser/parser.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "utils/utils.h"
#include "utils/lotusError.h"
#include <cmath>

using namespace lotus;

void lotus::Parser::loadMathModule() {
	static Module Math;

	Math.DEF("absolute", [] (Module& module) {
		if (!isNumber(module.GET("x"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("x")->getType(), module);
		if (module.GET("x")->getType() == STRING_LITERAL("int")) RETURN_VALUE(INT(std::abs(module.GET("x")->asInt(module))));
		RETURN_VALUE(FLOAT(std::abs(module.GET("x")->asDouble(module))));
		}, "x");

	Math.DEF("round", [](Module& module) {
		if (!isNumber(module.GET("x"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("x")->getType(), module);
		RETURN_VALUE(INT(module.GET("x")->asInt(module)));
		}, "x");

	Math.DEF("min", [](Module& module) {
		if (!isNumber(module.GET("x"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("x")->getType(), module);
		if (!isNumber(module.GET("y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("y")->getType(), module);
		RETURN_VALUE(FLOAT(std::min(module.GET("x")->asDouble(module), module.GET("y")->asDouble(module))));
		}, "x", "y");

	Math.DEF("max", [](Module& module) {
		if (!isNumber(module.GET("x"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("x")->getType(), module);
		if (!isNumber(module.GET("y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("y")->getType(), module);
		RETURN_VALUE(FLOAT(std::max(module.GET("x")->asDouble(module), module.GET("y")->asDouble(module))));
		}, "x", "y");

	Math.DEF("sqrt", [](Module& module) {
		if (!isNumber(module.GET("x"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("x")->getType(), module);
		RETURN_VALUE(FLOAT(std::sqrt(module.GET("x")->asDouble(module))));
		}, "x");

	Math.DEF("PI", [](Module& module) {
		RETURN_VALUE(FLOAT(3.14342354));
		});

	Math.DEF("E", [](Module& module) {
		RETURN_VALUE(FLOAT(2.7182818284));
		});

	modules.emplace(STRING_LITERAL("Math"), Math);
}
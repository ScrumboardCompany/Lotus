#include "parser/parser.h"
#include "parser/value/floatValue.h"
#include "parser/value/intValue.h"
#include <cmath>

using namespace lotus;

void lotus::Parser::loadMathModule() {
	Module Math;
	Static MathStatic;

	MathStatic.addMethod("absolute", METHOD(AccessModifierType::PUBLIC, [&] {
		if (module.GET("arg")->getType() == STRING_LITERAL("int")) RETURN_VALUE(INT(std::abs(module.GET("arg")->asInt(module))));
		RETURN_VALUE(FLOAT(std::abs(module.GET("arg")->asDouble(module))));
		}, "arg"));

	MathStatic.addMethod("round", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(INT(module.GET("arg")->asInt(module)));
		}, "arg"));

	MathStatic.addMethod("min", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(FLOAT(std::min(module.GET("arg1")->asDouble(module), module.GET("arg2")->asDouble(module))));
		}, "arg1", "arg2"));

	MathStatic.addMethod("max", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(FLOAT(std::max(module.GET("arg1")->asDouble(module), module.GET("arg2")->asDouble(module))));
		}, "arg1", "arg2"));

	MathStatic.addMethod("sqrt", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(FLOAT(std::sqrt(module.GET("arg")->asDouble(module))));
		}, "arg"));

	MathStatic.addMethod("PI", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(FLOAT(3.14342354));
		}));

	MathStatic.addMethod("E", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(FLOAT(2.7182818284));
		}));

	Math.STATIC("Math", MathStatic);
	modules.emplace(STRING_LITERAL("Math"), Math);
}
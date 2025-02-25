#pragma once

#ifndef _MODULE_
#define _MODULE_

#include "structures/variables.h"
#include "structures/functions.h"
#include "structures/statics.h"
#include "structures/classes.h"
#include "parser/statement/cppFunctionStatement.h"

#define LET(name, value) variables.declare(STRING_LITERAL(name), value)
#define SET(name, value) variables.set(STRING_LITERAL(name), value)
#define GET(name) variables.get(STRING_LITERAL(name))
#define DEF(name, body, ...) functions.declare(STRING_LITERAL(name), MAKE_CPP_FUNCTION(body, __VA_ARGS__))
#define CALL(module, name, ...) functions.call(name, {__VA_ARGS__}, module)
#define CALL_SPECIFY(module, name, args, specifiedArgs) functions.call(name, args, specifiedArgs, module)
#define STATIC(name, value) statics.declare(STRING_LITERAL(name), value)
#define CLASS(module, name, value) classes.declare(name, MAKE_PTR<Class>(value)).registerClass(name, module)
#define METHOD(accessModifier, body, ...) MethodMemberInfo(MAKE_CPP_FUNCTION(body, __VA_ARGS__), accessModifier)
#define FIELD(accessModifier, value) FieldMemberInfo(value, accessModifier)

namespace lotus {

	struct Module {
		Variables variables;
		Functions functions;
		Statics statics;
		Classes classes;
	};

}

#endif // _MODULE_
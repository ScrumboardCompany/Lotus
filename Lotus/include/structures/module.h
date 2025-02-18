#pragma once

#ifndef _MODULE_
#define _MODULE_

#include "structures/variables.h"
#include "structures/functions.h"
#include "structures/statics.h"
#include "parser/statement/cppFunctionStatement.h"

#define LET(name, value) variables.declare(STRING_LITERAL(name), value)
#define SET(name, value) variables.set(STRING_LITERAL(name), value)
#define DEF(name, body, ...) functions.declare(STRING_LITERAL(name), MAKE_CPP_FUNCTION(body, __VA_ARGS__))
#define STATIC(name, value) statics.declare(STRING_LITERAL(name), value)

namespace lotus {

	struct Module {
		Variables variables;
		Functions functions;
		Statics statics;
	};

}

#endif // _MODULE_
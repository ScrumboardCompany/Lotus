#pragma once

#ifndef _MODULE_
#define _MODULE_

#include "structures/variables.h"
#include "structures/functions.h"
#include "parser/statement/cppFunctionStatement.h"

#define LET(name, value) variables.declare(STRING_LITERAL(name), value)
#define SET(name, value) variables.set(STRING_LITERAL(name), value)
#define DEF(name, body, ...) functions.declare(STRING_LITERAL(name), Function(MAKE_PTR<CppFunctionStatement>(body), {__VA_ARGS__}, int()))

namespace lotus {

	struct Module {
		Variables variables;
		Functions functions;
	};

}

#endif // _MODULE_
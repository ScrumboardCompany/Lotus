#pragma once

#ifndef _CPPFUNTIONSTATEMENT_
#define _CPPFUNTIONSTATEMENT_

#include "parser/statement/statement.h"
#include <functional>

namespace lotus {

	class LOTUS_API CppFunctionStatement : public IStatement {
		ModuleBody_t body;

	public:
		CppFunctionStatement(const ModuleBody_t& body);

		void execute(Module& module) override;
	};
}

#endif // _CPPFUNTIONSTATEMENT_
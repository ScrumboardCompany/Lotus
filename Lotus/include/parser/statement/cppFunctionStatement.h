#pragma once

#ifndef _CPPFUNTIONSTATEMENT_
#define _CPPFUNTIONSTATEMENT_

#include "parser/statement/statement.h"
#include "structures/variables.h"
#include <functional>

namespace lotus {

	class CppFunctionStatement : public IStatement {
		std::function<void()> body;

	public:
		CppFunctionStatement(const std::function<void()>& body);

		void execute(Module&) override;
	};
}

#endif // _CPPFUNTIONSTATEMENT_
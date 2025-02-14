#pragma once

#ifndef _CPPFUNTIONSTATEMENT_
#define _CPPFUNTIONSTATEMENT_

#include "parser/statement/statement.h"
#include "structures/variables.h"
#include <functional>

namespace lotus {

	class CppFunctionStatement : public IStatement {

		Ptr<Variables> variables;
		std::function<void(Variables&)> body;

	public:
		CppFunctionStatement(const std::function<void(Variables&)>& body);
		void setVariables(Variables& variables);

		void execute() override;
	};
}

#endif // _CPPFUNTIONSTATEMENT_
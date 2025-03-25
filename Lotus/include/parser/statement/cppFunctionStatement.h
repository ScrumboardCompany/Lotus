#pragma once

#ifndef _CPPFUNTIONSTATEMENT_
#define _CPPFUNTIONSTATEMENT_

#include "parser/statement/statement.h"
#include <functional>

namespace lotus {

	class LOTUS_API CppFunctionStatement : public IStatement {
		std::function<void()> body;

	public:
		CppFunctionStatement(const std::function<void()>& body);

		void execute(Module&) override;
	};
}

#endif // _CPPFUNTIONSTATEMENT_
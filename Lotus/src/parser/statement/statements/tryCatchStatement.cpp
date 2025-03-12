#include "parser/statement/tryCatchStatement.h"
#include "utils/utils.h"
#include "structures/module.h"

using namespace lotus;

lotus::TryCatchStatement::TryCatchStatement(const Statement& tryBlock, String name, const Statement& catchBlock)
	: tryBlock(tryBlock), name(name), catchBlock(catchBlock) {}

void lotus::TryCatchStatement::execute(Module& module) {
	size_t scopesCount = module.variables.scopesCount();
	try {
		module.variables.enterScope();
		tryBlock->execute(module);
		module.variables.exitScope();
	}
	catch (ThrowValue value) {
		for (; scopesCount < module.variables.scopesCount(); module.variables.exitScope()) {}

		module.variables.enterScope();
		module.variables.declare(name, value.value);
		catchBlock->execute(module);
		module.variables.exitScope();
	}
}

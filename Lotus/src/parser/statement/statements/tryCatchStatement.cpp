#include "parser/statement/tryCatchStatement.h"
#include "utils/utils.h"
#include "structures/module.h"

using namespace lotus;

lotus::TryCatchStatement::TryCatchStatement(const Statement& tryBlock, String name, const Statement& catchBlock)
	: tryBlock(tryBlock), name(name), catchBlock(catchBlock) {}

void lotus::TryCatchStatement::execute(Module& module) {
	try {
		tryBlock->execute(module);
	}
	catch (ThrowValue value) {
		module.variables.enterScope();
		module.variables.declare(name, value.value);
		catchBlock->execute(module);
		module.variables.exitScope();
	}
}

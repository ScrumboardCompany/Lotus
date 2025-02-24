#include "parser/statement/blockStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::BlockStatement::BlockStatement(const std::vector<Statement>& statements) : statements(statements) {}

void lotus::BlockStatement::execute(Module& module) {
	for (auto& statement : statements) {
		if (statement) {
			statement->execute(module);
		}
	}
}
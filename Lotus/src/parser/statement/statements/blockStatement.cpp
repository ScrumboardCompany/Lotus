#include "parser/statement/blockStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::BlockStatement::BlockStatement(const std::vector<Statement>& statements) : statements(statements) {}

void lotus::BlockStatement::execute() {
	for (auto& statement : statements) {
		statement->execute();
	}
}
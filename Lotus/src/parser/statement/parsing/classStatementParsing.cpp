#include "parser/parser.h"
#include "parser/statement/classStatement.h"

using namespace lotus;

Statement lotus::Parser::handleClassStatement() {
	String name = consume(TokenType::WORD).text;

	auto classInfo = handleFieldsMethods();

	return MAKE_PTR<ClassStatement>(module.functions, module.variables, name, classInfo.first, classInfo.second);
}
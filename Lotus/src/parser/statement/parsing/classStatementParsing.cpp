#include "parser/parser.h"
#include "parser/statement/classStatement.h"

using namespace lotus;

Statement lotus::Parser::handleClassStatement() {
	String name = consume(TokenType::WORD).text;

	std::vector<String> parents;
	if (match(TokenType::COLON)) {

		while (true) {
			parents.push_back(consume(TokenType::WORD).text);

			if (!match(TokenType::COMMA)) {
				break;
			}
		}
	}

	auto classInfo = handleFieldsMethods();

	return MAKE_PTR<ClassStatement>(module.classes, module.functions, module.variables, name, classInfo.first, classInfo.second, parents);
}
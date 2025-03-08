#include "parser/parser.h"
#include "parser/statement/classStatement.h"

using namespace lotus;

Statement lotus::Parser::handleClassStatement() {
	String name = consume(TokenType::IDENTIFIER).text;

	std::vector<String> parents;
	if (match(TokenType::COLON)) {

		while (true) {
			parents.push_back(consume(TokenType::IDENTIFIER).text);

			if (!match(TokenType::COMMA)) {
				break;
			}
		}
	}

	auto classInfo = handleFieldsMethods();

	return MAKE_PTR<ClassStatement>(name, classInfo.first, classInfo.second, parents);
}
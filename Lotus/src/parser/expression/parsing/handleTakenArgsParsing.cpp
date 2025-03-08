#include "parser/parser.h"
#include "utils/lotusError.h"

using namespace lotus;

std::pair<std::vector<Expression>, StringMap<Expression>> lotus::Parser::handleTakenArgs() {
	std::vector<Expression> expressions;
	StringMap<Expression> specifiedExpressions;

	while (true) {
		if (get(0).type == TokenType::IDENTIFIER && get(1).type == TokenType::EQUALGREATER) {
			String name = consume(TokenType::IDENTIFIER).text;

			consume(TokenType::EQUALGREATER);

			specifiedExpressions.emplace(name, expression());
		}
		else if(specifiedExpressions.empty()) {
			expressions.push_back(expression());
		} 
		else {
			throw LotusException(STRING_LITERAL("Cannot specify regular agrument after specified argument"));
		}

		if (!match(TokenType::COMMA)) {
			break;
		}
	}

	return std::make_pair(expressions, specifiedExpressions);
}
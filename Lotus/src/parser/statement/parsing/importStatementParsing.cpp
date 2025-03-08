#include "parser/parser.h"
#include "parser/statement/importStatement.h"

using namespace lotus;

Statement Parser::handleImportStatement() {

	String key;

	if (match(TokenType::STAR)) {
		key = STRING_LITERAL("*");
	}
	else key = consume(TokenType::IDENTIFIER).text;

	consume(TokenType::LESSLESSLESS);

	String filePath;
	if (get(0).type == TokenType::IDENTIFIER) {
		filePath = consume(TokenType::IDENTIFIER).text;
	}
	else {
		filePath = consume(TokenType::STRING_TYPE).text;
	}

	return MAKE_PTR<ImportStatement>(key, filePath, modules);
}
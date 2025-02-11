#include "parser/parser.h"
#include "parser/statement/importStatement.h"

using namespace lotus;

Statement Parser::handleImportStatement() {

	String key;

	if (match(TokenType::STAR)) {
		key = STRING_LITERAL("*");
	}
	else key = consume(TokenType::WORD).text;

	consume(TokenType::LESSLESSLESS);

	String filePath = consume(TokenType::STRING_TYPE).text;

	return MAKE_PTR<ImportStatement>(key, filePath, variables, flags);
}
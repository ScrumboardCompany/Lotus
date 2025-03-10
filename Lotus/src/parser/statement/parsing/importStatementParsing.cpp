#include "parser/parser.h"
#include "parser/statement/importStatement.h"
#include "utils/lotusError.h"
#include <algorithm>

using namespace lotus;

Statement Parser::handleImportStatement() {

	std::vector<ImportElementInfo> elements;

	while (true) {
		ImportElementInfo element;

		if (match(TokenType::CLASS)) {
			element.type = KeyType::CLASS;
			element.stringType = STRING_LITERAL("class");
		}
		else if (match(TokenType::STATIC)) {
			element.type = KeyType::STATIC;
			element.stringType = STRING_LITERAL("static");
		}
		else if (match(TokenType::ENUM)) {
			element.type = KeyType::ENUM;
			element.stringType = STRING_LITERAL("enum");
		}
		else if (match(TokenType::FUNCTION)) {
			element.type = KeyType::FUNCTION;
			element.stringType = STRING_LITERAL("function");
		}
		else if (match(TokenType::VARIABLE)) {
			element.type = KeyType::VARIABLE;
			element.stringType = STRING_LITERAL("variable");
		}
		else {
			if (get(1).type == TokenType::IDENTIFIER || get(1).type == TokenType::STAR) {
				element.type = KeyType::UNKNOWN;
				element.stringType = consume(TokenType::IDENTIFIER).text;
			}
			element.type = KeyType::NOTYPE;
		}

		if (match(TokenType::STAR)) {
			element.key = STRING_LITERAL("*");
		}
		else {
			element.key = consume(TokenType::IDENTIFIER).text;
		}

		elements.push_back(element);

		if (!match(TokenType::COMMA)) {
			break;
		}
	}

	ptrdiff_t everythingCount = std::count_if(elements.begin(), elements.end(), [&](const ImportElementInfo& element) {
		return (element.key == STRING_LITERAL("*") && element.type == KeyType::NOTYPE);
		});

	if (everythingCount > 0 && elements.size() > 1) {
		throw LotusException(STRING_LITERAL("Can't specify what to import when importing everything"));
	}

	consume(TokenType::LESSLESSLESS);

	String filePath;
	if (get(0).type == TokenType::IDENTIFIER) {
		filePath = consume(TokenType::IDENTIFIER).text;
	}
	else {
		filePath = consume(TokenType::STRING_TYPE).text;
	}

	return MAKE_PTR<ImportStatement>(elements, filePath, modules);
}
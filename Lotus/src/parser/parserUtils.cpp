#include "parser/parser.h"
#include "utils/lotusError.h"
#include <unordered_set>

using namespace lotus;

Token lotus::Parser::get(const size_t relativePosition) {
	const size_t position = pos + relativePosition;
	if (position >= tokens.size()) return EOF_TOKEN;
	return tokens.at(position);
}

bool lotus::Parser::match(const TokenType type) {
	const Token currentToken = get(0);
	if (type != currentToken.type) return false;
	pos++;

	return true;
}

Token lotus::Parser::consume(const TokenType type) {
	const Token currentToken = get(0);
	if (type != currentToken.type) {
		throw LotusException(STRING_LITERAL("Expected ") + Token({ type, STRING_LITERAL("") }).type_to_string() + STRING_LITERAL(" instead of ") + currentToken.type_to_string(), currentToken.line);
	}
	pos++;

	return currentToken;
}


bool lotus::Parser::isValidImportStatement() {
    size_t i = 0;
    bool expectsComma = false;

    std::unordered_set<TokenType> requiresIdentifierOrStar = {
        TokenType::CLASS, TokenType::STATIC, TokenType::FUNCTION, TokenType::VARIABLE, TokenType::ENUM
    };

    while (i < tokens.size()) {
        if (expectsComma) {
            if (get(i).type != TokenType::COMMA) {
                break;
            }
            ++i;
            if (i >= tokens.size()) return false;
        }

        if (get(i).type == TokenType::STAR) {
            ++i;
        }
        else if (requiresIdentifierOrStar.find(get(i).type) != requiresIdentifierOrStar.end()) {
            ++i;
            if (i >= tokens.size() || (get(i).type != TokenType::IDENTIFIER && get(i).type != TokenType::STAR)) {
                return false;
            }
            ++i;
        }
        else if (get(i).type == TokenType::IDENTIFIER) {
            ++i;
        }
        else {
            return false;
        }

        expectsComma = true;
    }

    return (i < tokens.size() && get(i).type == TokenType::LESSLESSLESS);
}
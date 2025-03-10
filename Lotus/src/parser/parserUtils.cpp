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
	const Token CurrentToken = get(0);
	if (type != CurrentToken.type) return false;
	pos++;

	return true;
}

Token lotus::Parser::consume(const TokenType type) {
	const Token CurrentToken = get(0);
	if (type != CurrentToken.type) {
		throw LotusException(STRING_LITERAL("Expected ") + Token({ type, STRING_LITERAL("") }).type_to_string() + STRING_LITERAL(" instead of ") + CurrentToken.type_to_string());
	}
	pos++;

	return CurrentToken;
}


bool lotus::Parser::isValidImportStatement() {
    //size_t i = 0;
    //bool expectsComma = false;

    //std::unordered_set<TokenType> requiresIdentifierOrStar = {
    //    TokenType::CLASS, TokenType::STATIC, TokenType::FUNCTION, TokenType::VARIABLE
    //};

    //while (i < tokens.size()) {
    //    if (expectsComma) {
    //        if (get(i).type != TokenType::COMMA) {
    //            throw LotusException(STRING_LITERAL("Expected \",\" between import elements"));
    //        }
    //        ++i;
    //        if (i >= tokens.size()) {
    //            throw LotusException(STRING_LITERAL("Unexpected \",\" at the end of import statement"));
    //        }
    //    }

    //    if (get(i).type == TokenType::STAR) {
    //        ++i;
    //    }
    //    else if (requiresIdentifierOrStar.find(get(i).type) != requiresIdentifierOrStar.end()) {
    //        ++i;
    //        if (i >= tokens.size()) {
    //            throw LotusException(STRING_LITERAL("Expected identifier or \"*\" after type"));
    //        }
    //        if (get(i).type != TokenType::IDENTIFIER && get(i).type != TokenType::STAR) {
    //            throw LotusException(STRING_LITERAL("Invalid element after type, expected identifier or \"*\""));
    //        }
    //        ++i;
    //    }
    //    else if (get(i).type == TokenType::IDENTIFIER) {
    //        ++i;
    //    }
    //    else {
    //        throw LotusException(STRING_LITERAL("Invalid token in import statement"));
    //    }

    //    expectsComma = true;
    //}

    //if (i >= tokens.size() || get(i).type != TokenType::LESSLESSLESS) {
    //    throw LotusException(STRING_LITERAL("Missing \"<<<\" at the end of import statement"));
    //}

    //return true;


    size_t i = 0;
    bool expectsComma = false;

    std::unordered_set<TokenType> requiresIdentifierOrStar = {
        TokenType::CLASS, TokenType::STATIC, TokenType::FUNCTION, TokenType::VARIABLE
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
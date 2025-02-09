#include "lexer/token.h"
#include "utils/lotusDefines.h"

using namespace lotus;

std::string lotus::Token::to_string() const {
	switch (type) {
	case lotus::TokenType::INT_TYPE:
		return ("int number");
	case lotus::TokenType::FLOAT_TYPE:
		return ("float number");
	case lotus::TokenType::WORD:
		return ("word");
	case lotus::TokenType::STRING_TYPE:
		return ("string");
	case lotus::TokenType::PLUS:
		return ("plus");
	case lotus::TokenType::MINUS:
		return ("enum");
	case lotus::TokenType::STAR:
		return ("star");
	case lotus::TokenType::SLASH:
		return ("slash");
	case lotus::TokenType::EQUAL:
		return ("equal");
	case lotus::TokenType::PRINT:
		return ("print");
	case lotus::TokenType::LET:
		return ("let");
	case lotus::TokenType::LPAREN:
		return ("left parentheses");
	case lotus::TokenType::RPAREN:
		return ("right parentheses");
	case lotus::TokenType::UNDEFINED_:
		return ("undefined");
	default:
		return ("undefined token");
	}
}
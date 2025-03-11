#include "lexer/token.h"
#include "utils/lotusDefines.h"

using namespace lotus;

String lotus::Token::type_to_string() const {
	switch (type) {
	case lotus::TokenType::INT_TYPE:
		return STRING_LITERAL("int");
	case lotus::TokenType::FLOAT_TYPE:
		return STRING_LITERAL("float");
	case lotus::TokenType::STRING_TYPE:
		return STRING_LITERAL("string");
	case lotus::TokenType::IDENTIFIER:
		return STRING_LITERAL("identifier");
	case lotus::TokenType::HEX:
		return STRING_LITERAL("hex");
	case lotus::TokenType::END_OF_FILE:
		return STRING_LITERAL("end of file");
	default:
		return text;
	}
}
#include "lexer/token.h"
#include "utils/lotusDefines.h"

using namespace lotus;

String lotus::Token::type_to_string() const {
	switch (type) {
	case lotus::TokenType::INT_TYPE:
		return STRING_LITERAL("int type");
	case lotus::TokenType::FLOAT_TYPE:
		return STRING_LITERAL("float type");
	case lotus::TokenType::STRING_TYPE:
		return STRING_LITERAL("string type");
	case lotus::TokenType::WORD:
		return STRING_LITERAL("word");
	case lotus::TokenType::PLUS:
		return STRING_LITERAL("+");
	case lotus::TokenType::MINUS:
		return STRING_LITERAL("-");
	case lotus::TokenType::STAR:
		return STRING_LITERAL("*");
	case lotus::TokenType::SLASH:
		return STRING_LITERAL("/");
	case lotus::TokenType::EQUAL:
		return STRING_LITERAL("=");
	case lotus::TokenType::GREATER:
		return STRING_LITERAL(">");
	case lotus::TokenType::LESS:
		return STRING_LITERAL("<");
	case lotus::TokenType::GREATEREQUAL:
		return STRING_LITERAL(">=");
	case lotus::TokenType::LESSEQUAL:
		return STRING_LITERAL("<=");
	case lotus::TokenType::EQUALEQUAL:
		return STRING_LITERAL("==");
	case lotus::TokenType::NOTEQUAL:
		return STRING_LITERAL("!=");
	case lotus::TokenType::BARBAR:
		return STRING_LITERAL("||");
	case lotus::TokenType::AMPAMP:
		return STRING_LITERAL("&&");
	case lotus::TokenType::NOT:
		return STRING_LITERAL("!");
	case lotus::TokenType::COMMA:
		return STRING_LITERAL(",");
	case lotus::TokenType::LET:
		return STRING_LITERAL("let");
	case lotus::TokenType::IF:
		return STRING_LITERAL("if");
	case lotus::TokenType::ELSE:
		return STRING_LITERAL("else");
	case lotus::TokenType::WHILE:
		return STRING_LITERAL("while");
	case lotus::TokenType::UNDEFINED_:
		return STRING_LITERAL("undefined");
	case lotus::TokenType::TRUE:
		return STRING_LITERAL("true");
	case lotus::TokenType::FALSE:
		return STRING_LITERAL("false");
	case lotus::TokenType::FOR:
		return STRING_LITERAL("for");
	case lotus::TokenType::LPAREN:
		return STRING_LITERAL("(");
	case lotus::TokenType::RPAREN:
		return STRING_LITERAL(")");
	case lotus::TokenType::LBRACE:
		return STRING_LITERAL("{");
	case lotus::TokenType::RBRACE:
		return STRING_LITERAL("}");
	case lotus::TokenType::SEMICOLON:
		return STRING_LITERAL(";");
	case lotus::TokenType::END_OF_FILE:
	default:
		return STRING_LITERAL("END_OF_FILE");
	}
}
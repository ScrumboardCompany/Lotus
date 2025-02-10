#include "parser/parser.h"
#include "utils/lotusError.h"

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
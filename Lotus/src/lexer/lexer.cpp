#include "lexer/lexer.h"
#include "utils/lotusError.h"
#include <cwctype>

using namespace lotus;

lotus::Lexer::Lexer(const String& input) : input(input), tokens(), pos(0) {}

std::list<Token> lotus::Lexer::tokenize() {
    while (pos < input.length()) {
        Char current = peek(0);

        if (std::iswdigit(current)) tokenizeNumber();
        else if (isWordChar(current, false)) tokenizeWord();
        else if (current == CHAR_LITERAL('\"')) tokenizeText();
        else if (current == CHAR_LITERAL('/') && peek(1) == CHAR_LITERAL('*')) tokenizeMultiComment();
        else if (current == CHAR_LITERAL('#')) tokenizeComment();
        else if (isStartOperator(current)) tokenizeOperator();

        else next();       
    }
    return tokens;
}

void lotus::Lexer::tokenizeNumber() {
    String buffer;
    Char current = peek(0);
    bool hasDot = false;

    while (true) {
        if (current == CHAR_LITERAL('.')) {
            if (hasDot) {
                throw LotusException(STRING_LITERAL("Can`t place two points in number: ") + buffer);
            }
            if (!std::iswdigit(peek(1))) {
                throw LotusException(STRING_LITERAL("Expected digit after ."));
            }
            hasDot = true;
        }

        if (!iswdigit(current) && current != CHAR_LITERAL('.')) {
            break;
        }

        buffer.push_back(current);
        current = next();
    }

    addToken(hasDot ? TokenType::FLOAT_TYPE : TokenType::INT_TYPE, buffer);
}

void lotus::Lexer::tokenizeWord() {
    String buffer;
    Char current = peek(0);
    while (isWordChar(current)) {
        buffer.push_back(current);
        current = next();
    }
    if (keywords.find(buffer) != keywords.end()) {
        addToken(keywords[buffer], buffer);
    }
    else {
        addToken(TokenType::WORD, buffer);
    }
}

void lotus::Lexer::tokenizeText() {
    next();
    String buffer;
    Char current = peek(0);
    while (current != CHAR_LITERAL('\"')) {
        if (current == CHAR_LITERAL('\0'))
            throw LotusException(STRING_LITERAL("No closing found \""));
        if (current == CHAR_LITERAL('\\')) {
            current = next();

            if (current == CHAR_LITERAL('\"')) {
                current = next();
                buffer.push_back(CHAR_LITERAL('\"'));
                continue;
            }
            else if (current == CHAR_LITERAL('n')) {
                current = next();
                buffer.push_back(CHAR_LITERAL('\n'));
                continue;
            }
            else if (current == CHAR_LITERAL('t')) {
                current = next();
                buffer.push_back(CHAR_LITERAL('\t'));
                continue;
            }
            else {
                buffer.push_back(CHAR_LITERAL('\\'));
                continue;
            }
        }
        buffer.push_back(current);
        current = next();
    }
    next();
    addToken(TokenType::STRING_TYPE, buffer);
}

void lotus::Lexer::tokenizeOperator() {
    size_t maxLength = 0;
    for (const auto& op : operators) {
        if (op.first.size() > maxLength) {
            maxLength = op.first.size();
        }
    }

    for (size_t length = maxLength; length > 0; --length) {
        if (pos + length > input.size()) {
            continue;
        }

        String potentialOp = input.substr(pos, length);
        auto it = operators.find(potentialOp);
        if (it != operators.end()) {
            addToken(it->second, potentialOp);
            pos += length;
            return;
        }
    }
}

void lotus::Lexer::tokenizeComment() {
    Char current = peek(0);

    std::vector<Char> stops = {
        CHAR_LITERAL('\n'),
        CHAR_LITERAL('\r'),
        CHAR_LITERAL('\0'),
    };

    while (std::find(stops.begin(), stops.end(), current) == stops.end()) {
        current = next();
    }
}

void lotus::Lexer::tokenizeMultiComment() {
    next();
    next();
    Char current = peek(0);
    while (!(current == CHAR_LITERAL('*') && peek(1) == CHAR_LITERAL('/'))) {
        if (current == CHAR_LITERAL('\0')) throw LotusException(STRING_LITERAL("Missing comment closing"));
        current = next();
    }
    next();
    next();
}

Char lotus::Lexer::peek(const size_t relativePosition) const {
    const size_t position = pos + relativePosition;
    if (position >= input.length()) return CHAR_LITERAL('\0');
    return input[position];
}

Char lotus::Lexer::next() {
    pos++;
    return peek(0);
}

void lotus::Lexer::addToken(const TokenType& type, const String& text) {
    tokens.push_back(Token({ type, text }));
}

bool lotus::Lexer::isStartOperator(Char ch) {
    for (auto& op : operators) {
        if (op.first.size() && op.first[0] == ch) {
            return true;
        }
    }
    return false;
}

bool lotus::Lexer::isWordChar(Char ch, bool checkNumber) {
    return (checkNumber ? std::iswalnum(ch) : std::iswalpha(ch)) || ch == CHAR_LITERAL('_') || ch == CHAR_LITERAL('$');
}

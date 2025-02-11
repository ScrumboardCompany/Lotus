#include "parser/statement/importStatement.h"
#include "utils/utils.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::ImportStatement::ImportStatement(const String& key, const String& filePath, Variables& variables, const Flags& flags)
    : key(key), filePath(filePath), variables(variables), flags(flags) {}

void lotus::ImportStatement::execute() {
    lotus::String content = lotus::wreadContent(filePath);

    Lexer lexer(content);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);

    auto statements = parser.parse();

    for (auto& statement : statements) {
        statement->execute();
    }

    bool allowOverwrite = flags.getAllowOverwrite();

    if (key == STRING_LITERAL("*") /* check need to import all */) {
        for (auto& variable : parser.variables.variables) {

            if (allowOverwrite) {
                variables.forceDeclareOrSet(variable.first, variable.second);
            }
            else variables.declare(variable.first, variable.second);
        }
    }
    else if (parser.variables.isExists(key)) {

        if (allowOverwrite) {
            variables.forceDeclareOrSet(key, parser.variables.get(key));
        }
        else variables.declare(key, parser.variables.get(key));
    }
    /*else if (parser.functions.isExists(key)) {
        functions.declare(parser.functions.get(key));   // note for future
    }*/
    else {
        throw LotusException(STRING_LITERAL("\"") + key + STRING_LITERAL("\"") + 
            String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
    }
}

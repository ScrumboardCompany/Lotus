#include "parser/statement/importStatement.h"
#include "utils/utils.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "structures/variables.h"
#include "utils/lotusError.h"
#include "structures/classes.h"
#include <algorithm>
#include "parser/expression/letExpression.h"
#include "parser/expression/stringExpression.h"
#include "parser/expression/floatExpression.h"
#include "parser/statement/expressionStatement.h"
#include <filesystem>

using namespace lotus;

void lotus::ImportStatement::loadFromModule(Module& from, Module& to) {
    bool importEverythingWithSameName = to.flags.getImportEverythingWithSameName();
    if (elements.empty()) throw LotusException(STRING_LITERAL("No elements to import specified"));
    bool importAll = (elements[0].key == STRING_LITERAL("*") && elements[0].type == KeyType::NOTYPE);

    for (auto& [key, type, stringType] : elements) {
        if (importAll) {
            for (auto& cls : from.classes.classes) {
                to.classes.forceSet(cls.first, cls.second);
            }
            for (auto& stat : from.statics.statics) {
                to.statics.forceSet(stat.first, stat.second);
            }
            for (auto& en : from.enums.enums) {
                to.enums.forceSet(en.first, en.second);
            }
            for (auto& func : from.functions.functions) {
                for (auto& overload : func.second) {
                    to.functions.forceSet(func.first, overload);
                }
            }
            if (!from.variables.scopes.empty()) {
                for (auto& var : from.variables.scopes[0]) {
                    to.variables.forceSet(var.first, var.second);
                }
            }
        }
        else if (type != KeyType::NOTYPE) {
            if (type == KeyType::UNKNOWN) {
                throw LotusException(stringType + STRING_LITERAL(" is unknown type"));
            }

            if (from.classes.isExists(key) && type == KeyType::CLASS) {
                to.classes.forceSet(key, from.classes.get(key));
                to.classes.registerClass(key, to);
                continue;
            } else if (key == STRING_LITERAL("*") && type == KeyType::CLASS) {
                for (auto& cls : from.classes.classes) {
                    to.classes.forceSet(cls.first, cls.second);
                    to.classes.registerClass(cls.first, to);
                }
                continue;
            }

            if (from.statics.isExists(key) && type == KeyType::STATIC) {
                to.statics.forceSet(key, from.statics.get(key));
                continue;
            } else if (key == STRING_LITERAL("*") && type == KeyType::STATIC) {
                for (auto& stat : from.statics.statics) {
                    to.statics.forceSet(stat.first, stat.second);
                }
                continue;
            }

            if (from.enums.isExists(key) && type == KeyType::ENUM) {
                to.enums.forceSet(key, from.enums.get(key));
                continue;
            }
            else if (key == STRING_LITERAL("*") && type == KeyType::ENUM) {
                for (auto& en : from.enums.enums) {
                    to.enums.forceSet(en.first, en.second);
                }
                continue;
            }

            if (from.functions.isExists(key) && type == KeyType::FUNCTION) {
                for (auto& f : from.functions.functions[key]) {
                    to.functions.forceSet(key, f);
                }
                continue;
            } else if (key == STRING_LITERAL("*") && type == KeyType::FUNCTION) {
                for (auto& func : from.functions.functions) {
                    for (auto& overload : func.second) {
                        to.functions.forceSet(func.first, overload);
                    }
                }
                continue;
            }

            if (from.variables.isExists(key) && type == KeyType::VARIABLE) {
                to.variables.forceSet(key, from.variables.get(key));
                continue;
            } else if (key == STRING_LITERAL("*") && type == KeyType::VARIABLE) {
                if (!from.variables.scopes.empty()) {
                    for (auto& var : from.variables.scopes[0]) {
                        to.variables.forceSet(var.first, var.second);
                    }
                }
                continue;
            }

            throw LotusException(stringType + STRING_LITERAL(" \"") + key + STRING_LITERAL("\"") +
                String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
        }
        else {
            bool found = false;
            if (from.classes.isExists(key)) {
                to.classes.forceSet(key, from.classes.get(key));
                if (!importEverythingWithSameName) {
                    to.classes.registerClass(key, to);
                }
                found = true;
            }

            if (from.statics.isExists(key)) {
                if (importEverythingWithSameName || !found) {
                    to.statics.forceSet(key, from.statics.get(key));
                    found = true;
                }
            }

            if (from.enums.isExists(key)) {
                if (importEverythingWithSameName || !found) {
                    to.enums.forceSet(key, from.enums.get(key));
                    found = true;
                }
            }

            if (from.functions.isExists(key)) {
                if (importEverythingWithSameName || !found) {
                    for (auto& f : from.functions.functions[key]) {
                        to.functions.forceSet(key, f);
                    }
                    found = true;
                }
            }

            if (from.variables.isExists(key)) {
                if (importEverythingWithSameName || !found) {
                    to.variables.forceSet(key, from.variables.get(key));
                    found = true;
                }
            }

            if (!found) throw LotusException(STRING_LITERAL("\"") + key + STRING_LITERAL("\"") +
                String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
        }
    }
}

lotus::ImportStatement::ImportStatement(const std::vector<ImportElementInfo>& elements, const String& filePath, StringMap<Module>& modules)
    : elements(elements), filePath(filePath), modules(modules) {}

void lotus::ImportStatement::execute(Module& currentModule) {
    size_t find = filePath.find_last_of(CHAR_LITERAL('/'));
    String file = (find != String::npos) ? filePath.substr(find + 1) : filePath;

    Module module;

    if (file.find(CHAR_LITERAL('.')) != String::npos) {
        String content = lotus::wreadContent(filePath);
        Lexer lexer(content);

        auto tokens = lexer.tokenize();

        parser = MAKE_PTR<Parser>(tokens);

        auto statements = parser->parse();

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__file__"),
                MAKE_PTR<StringExpression>(std::filesystem::path(filePath).filename().wstring())
            )));

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__path__"),
                MAKE_PTR<StringExpression>(std::filesystem::absolute(filePath).wstring())
            )));

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__version__"),
                MAKE_PTR<FloatExpression>(LOTUS_VERSION)
            )));

        for (auto& statement : statements) {
            if (statement) statement->execute(parser->getModule());
        }
        module = parser->getModule();
    }
    else {
        if (modules.find(file) == modules.end()) {
            throw LotusException(STRING_LITERAL("Module: ") + file + STRING_LITERAL(" not found"));
        }
        module = modules[file];
    }

    loadFromModule(module, currentModule);
}
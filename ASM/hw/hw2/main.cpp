#include <iostream>
#include <string>
#include <vector>
#include <cctype>

namespace Lexem {
    enum Type {
        UNKNOWN,
        TYPE,
        ID,
        LPAREN,
        RPAREN,
        LBRACKET,
        RBRACKET,
        STAR,
        COMMA,
        SEMICOLON,
        NUMBER,
        COUNT
    };
}

namespace State {
    enum Type {
        ERROR,
        START,
        TYPE,
        ID,
        LPAREN,
        PARAM_LIST, // Переименовано PARAMS -> PARAM_LIST для ясности
        PARAM_STAR,
        ARRAY_DIM, // Переименовано NUMBER -> ARRAY_DIM для ясности
        NUMBER,
        RPAREN,
        END,
        COUNT
    };
}

// Таблица переходов автомата (исправлена)
static const State::Type transitionTable[State::COUNT][Lexem::COUNT] = {
        //  UNKNOWN  TYPE    ID      LPAREN  RPAREN  LBRACKET  RBRACKET  STAR  COMMA  SEMICOLON  NUMBER
        /* ERROR */      {State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
        /* START */      {State::ERROR,      State::TYPE,       State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
        /* TYPE */       {State::ERROR,      State::ERROR,      State::ID,         State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::PARAM_STAR, State::ERROR,   State::ERROR,      State::ERROR},
        /* ID */        {State::ERROR,      State::ERROR,      State::ERROR,      State::LPAREN,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
        /* LPAREN */    {State::ERROR,      State::TYPE,       State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
        /* PARAM_LIST */{State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::RPAREN,     State::ERROR,   State::ERROR,   State::ERROR,      State::TYPE,    State::ERROR,      State::TYPE},  // Исправлено
        /* PARAM_STAR */{State::ERROR,      State::ERROR,      State::ID,         State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::PARAM_STAR, State::ERROR,   State::ERROR,      State::ERROR},
        /* ARRAY_DIM */  {State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::NUMBER,  State::PARAM_LIST,  State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR}, // Исправлено
        /* NUMBER */    {State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ARRAY_DIM,    State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
        /* RPAREN */    {State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::END,       State::ERROR},
        /* END */       {State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,      State::ERROR,   State::ERROR,   State::ERROR,      State::ERROR,   State::ERROR,      State::ERROR},
};


Lexem::Type getLexemType(const std::string& token) {
    if (token == "void" || token == "int" || token == "double" || token == "float" ||
        token == "char" || token == "bool" || token=="long") {
        return Lexem::TYPE;
    } else if (isalpha(token[0]) || token[0] == '_') {
        for (size_t i = 1; i < token.size(); ++i) {
            if (!isalnum(token[i]) && token[i] != '_') {
                return Lexem::UNKNOWN;
            }
        }
        return Lexem::ID;
    } else if (token == "(") {
        return Lexem::LPAREN;
    } else if (token == ")") {
        return Lexem::RPAREN;
    } else if (token == "[") {
        return Lexem::LBRACKET;
    } else if (token == "]") {
        return Lexem::RBRACKET;
    } else if (token == "*") {
        return Lexem::STAR;
    } else if (token == ",") {
        return Lexem::COMMA;
    } else if (token == ";") {
        return Lexem::SEMICOLON;
    } else if (isdigit(token[0])) {
        for (size_t i = 1; i < token.size(); ++i) {
            if (!isdigit(token[i])) {
                return Lexem::UNKNOWN;
            }
        }
        return Lexem::NUMBER;
    } else {
        return Lexem::UNKNOWN;
    }
}

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (isspace(c) || c == '(' || c == ')' || c == '[' || c == ']' || c == ',' || c == ';') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            if (!isspace(c)) {
                tokens.push_back(std::string(1, c));
            }
        } else if (c == '*') { // Обработка '*'
            if (!currentToken.empty()) { // Если перед '*' есть символы, добавляем их как токен
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back("*"); // Добавляем '*' как отдельный токен
        } else {
            currentToken += c;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    std::cout << "TOKENS:\n";
    for (auto& t: tokens) {
        std::cout << t << std::endl;
    }
    return tokens;
}

void printResults(const std::string& functionType,
                  const std::string& functionName,
                  const std::vector<std::pair<std::string, std::pair<std::string, std::vector<int>>>>& parameters) {
    std::cout << "Function type: " << functionType << std::endl;
    std::cout << "Function name: " << functionName << std::endl;
    std::cout << "Parameters: " << std::endl;
    for (const auto& param : parameters) {
        std::cout << "  " << param.first << " "
                  << param.second.first << ": ";
        for (int dim : param.second.second) {
            std::cout << "[" << dim << "]";
        }
        std::cout << std::endl;
    }
}

bool analyze(const std::vector<std::string>& tokens) {
    State::Type currentState = State::START;
    std::string functionType;
    std::string functionName;
    std::vector<std::pair<std::string, std::pair<std::string, std::vector<int>>>> parameters;
    std::pair<std::string, std::pair<std::string, std::vector<int>>> currentParam;

    for (const std::string& token : tokens) {
        Lexem::Type lexemType = getLexemType(token);
        currentState = transitionTable[currentState][lexemType];

        switch (currentState) {
            case State::TYPE:
                if (functionType.empty())
                    functionType = token;
                else
                    currentParam.first = token; // Тип параметра
                break;
            case State::ID:
                if (functionName.empty()) {
                    functionName = token;
                } else {
                    currentParam.second.first = token;
                }
                break;
            case State::PARAM_STAR: // Обработка указателей
                currentParam.first += "*";
                break;
            case State::NUMBER:
                currentParam.second.second.push_back(std::stoi(token));
                break;
            case State::PARAM_LIST:
                if (!currentParam.second.first.empty()){
                    parameters.push_back(currentParam);
                }
                currentParam = {};
                break;
            case State::ERROR:
                if (!currentParam.second.first.empty()){
                    parameters.push_back(currentParam);
                }
                printResults(functionType, functionName, parameters);
                std::cout << "Error: Invalid syntax." << std::endl;
                return false;
            case State::END:
                if (!currentParam.second.first.empty()){
                    parameters.push_back(currentParam);
                }
                printResults(functionType, functionName, parameters);
                return true;
            default:
                break;
        }
    }

    return false;
}

int main() {
    std::string input;
    std::cout << "Enter procedure declaration: ";
    std::getline(std::cin, input);

    std::vector<std::string> tokens = tokenize(input);
    analyze(tokens);

    std::cout << getLexemType("**kk");
    return 0;
}
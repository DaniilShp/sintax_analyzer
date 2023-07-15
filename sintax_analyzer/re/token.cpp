#pragma once

#include "token.h"

bool Token::IsIdentifier(const std::string& str)
{
    for (char c : str) {
        if (!((c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || c == '_'))
            return false;
    }
    return true;
}

token_type Token::FindType(const std::string& tkn) // для каждого подтипа запроса будет своя функция, так как будет разный полный набор токенов
{                                                  // либо передавать бинарную маску сначала в get tokens а потом и сюда, чтобы проводить не все проверки
    if (tkn._Equal("create") || tkn._Equal("table") || tkn._Equal("alter") || tkn._Equal("drop")) return token_type::MainOperator;
    if (tkn._Equal("(")) return token_type::LPAR;   // для create table 6-7 типов токенов, для alter 10+, для drop 3-4, для select 15+
    if (tkn._Equal(")")) return token_type::RPAR;
    if (tkn._Equal(",")) return token_type::COMMA;
    if (tkn._Equal("int") || tkn._Equal("date") || tkn._Equal("time") || tkn._Equal("text")) return token_type::VariableType; //varchar(x) сложнее, пока text
    if (tkn._Equal("add") || tkn._Equal("drop") || tkn._Equal("modify")) return token_type::SecondaryOperator;
    if (tkn._Equal(";")) return token_type::SMCLN;
    if (IsIdentifier(tkn)) return token_type::Identifier; // проверит нет ли др спецспецсимволов
    else return token_type::Error;
}

std::vector<Token> Token::GetTokens(const std::string& str) {
    std::vector<Token> tokens; // список слов
    std::string token; // текущее слово
    std::array<char, 11> separators = { ' ', '\t', '\n', '(', ')', '[', '{', '}', '.', ',', ';'};
    for (char c : str) { // проходим по каждому символу в строке
        if (std::find(separators.begin(), separators.end(), c) != separators.end()) { // если символ является разделителем
            if (!token.empty()) { // если текущее слово не пустое
                tokens.push_back(Token(token)); // добавляем его в список слов
                token.clear(); // очищаем текущее слово
            }
            if (c != ' ' && c != '\t' && c != '\n') {
                tokens.push_back(Token(std::string(1, c)));
            }
        }
        else { // иначе добавляем символ в текущее слово
            token += c;
        }
    }
    if (!token.empty()) { // добавляем оставшееся слово в список (если оно есть)
        tokens.push_back(Token(token));
    }
    return tokens; // возвращаем список слов
}


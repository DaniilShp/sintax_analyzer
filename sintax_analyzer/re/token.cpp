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

token_type Token::FindType(const std::string& tkn) // ��� ������� ������� ������� ����� ���� �������, ��� ��� ����� ������ ������ ����� �������
{                                                  // ���� ���������� �������� ����� ������� � get tokens � ����� � ����, ����� ��������� �� ��� ��������
    if (tkn._Equal("create") || tkn._Equal("table") || tkn._Equal("alter") || tkn._Equal("drop")) return token_type::MainOperator;
    if (tkn._Equal("(")) return token_type::LPAR;   // ��� create table 6-7 ����� �������, ��� alter 10+, ��� drop 3-4, ��� select 15+
    if (tkn._Equal(")")) return token_type::RPAR;
    if (tkn._Equal(",")) return token_type::COMMA;
    if (tkn._Equal("int") || tkn._Equal("date") || tkn._Equal("time") || tkn._Equal("text")) return token_type::VariableType; //varchar(x) �������, ���� text
    if (tkn._Equal("add") || tkn._Equal("drop") || tkn._Equal("modify")) return token_type::SecondaryOperator;
    if (tkn._Equal(";")) return token_type::SMCLN;
    if (IsIdentifier(tkn)) return token_type::Identifier; // �������� ��� �� �� ����������������
    else return token_type::Error;
}

std::vector<Token> Token::GetTokens(const std::string& str) {
    std::vector<Token> tokens; // ������ ����
    std::string token; // ������� �����
    std::array<char, 11> separators = { ' ', '\t', '\n', '(', ')', '[', '{', '}', '.', ',', ';'};
    for (char c : str) { // �������� �� ������� ������� � ������
        if (std::find(separators.begin(), separators.end(), c) != separators.end()) { // ���� ������ �������� ������������
            if (!token.empty()) { // ���� ������� ����� �� ������
                tokens.push_back(Token(token)); // ��������� ��� � ������ ����
                token.clear(); // ������� ������� �����
            }
            if (c != ' ' && c != '\t' && c != '\n') {
                tokens.push_back(Token(std::string(1, c)));
            }
        }
        else { // ����� ��������� ������ � ������� �����
            token += c;
        }
    }
    if (!token.empty()) { // ��������� ���������� ����� � ������ (���� ��� ����)
        tokens.push_back(Token(token));
    }
    return tokens; // ���������� ������ ����
}


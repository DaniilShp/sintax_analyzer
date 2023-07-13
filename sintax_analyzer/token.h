#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>

enum class token_type
{
    Error = -1,
    Identifier,
    MainOperator,
    SecondaryOperator,
    VariableType,
    constant,
    LBRA, // {
    RBRA, // }
    LPAR, // (
    RPAR, // )
    LSQR, // [
    RSQR, // ]
    DOT,  // .
    COMMA, // ,
    SMCLN  // ; semicolon
};

class Token
{
private:
    std::string name;
    token_type type;
    token_type FindType(const std::string&);
public:
    Token(const std::string& tkn) { name = tkn; type = this->FindType(tkn); };
    token_type GetType() { return this->type; };
    std::string GetName() { return this->name; };
    bool IsIdentifier(const std::string& str);
    std::vector<Token>* GetTokens(const std::string& str);

};

bool Token::IsIdentifier(const std::string& str)
{
    for (char c : str) {
        if (!((c <= 'z' && c >='a') || (c <= '9' && c >= '0') || c == '_'))
            return false;
    }
    return true;
}

token_type Token::FindType(const std::string& tkn) // ��� ������� ������� ������� ����� ���� �������, ��� ��� ����� ������ ������ ����� �������
{
    if (tkn._Equal("create") || tkn._Equal("table")) return token_type::MainOperator;
    if (tkn._Equal("(")) return token_type::LPAR;   // ��� create table 6-7 ����� �������, ��� alter 10+, ��� drop 3-4, ��� select 15+
    if (tkn._Equal(")")) return token_type::RPAR;
    if (tkn._Equal(",")) return token_type::COMMA;
    if (tkn._Equal("int") || tkn._Equal("date") || tkn._Equal("time")) return token_type::VariableType;
    if (tkn._Equal("add") || tkn._Equal("drop") || tkn._Equal("rename")) return token_type::SecondaryOperator;
    if (tkn._Equal(";")) return token_type::SMCLN;
    if (IsIdentifier(tkn)) return token_type::Identifier; // �������� ��� �� �� ����������������
    else return token_type::Error;
}

std::vector<Token>* Token::GetTokens(const std::string& str) {
    std::vector<Token>* tokens = new std::vector<Token>(); // ������ ����
    std::string token; // ������� �����
    std::array<char, 10> separators = {' ', '\t', '\n', '(', ')', '[', '{', '}', '.', ','};
    for (char c : str) { // �������� �� ������� ������� � ������
        if (std::find(separators.begin(), separators.end(), c) != separators.end()) { // ���� ������ �������� ������������
            if (!token.empty()) { // ���� ������� ����� �� ������
                tokens->push_back(Token(token)); // ��������� ��� � ������ ����
                token.clear(); // ������� ������� �����
            }
            if (c != ' ' && c != '\t' && c != '\n') {
                tokens->push_back(Token(std::string(1, c)));
            }
        }
        else { // ����� ��������� ������ � ������� �����
            token += c;
        }
    }
    if (!token.empty()) { // ��������� ���������� ����� � ������ (���� ��� ����)
        tokens->push_back(Token(token));
    }
    return tokens; // ���������� ������ ����
}

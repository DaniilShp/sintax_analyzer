#pragma once

const int CommandsAmount = 3;

enum class CommandType { // пример использования: CommandNames[(int)CommandType::CREATE] = "create table" и с CommandTypesFunctions работает аналогично
	CREATE,
	ALTER,
	DROP
};

const std::string CommandNames[CommandsAmount] = { // статический массив для основоных операторов, с которых может начинаться запрос
	"create table",
	"alter table",
	"drop table"
};

class Analyzer
{
private:
	std::string command;
	void initialise();
	bool StrStartsWith(std::string);
public:
	Analyzer();
	bool AnaliseCreateTable();
	bool AnaliseAlterTable();
	bool AnaliseDropTable();
	bool StartAnalis(std::string command);

};

typedef bool (Analyzer::* TypeCommandAnalise)();		//тип данных, представляющий собой указатель на метод

const TypeCommandAnalise CommandTypesFunctions[CommandsAmount] = { // статический массив для основоных операторов, с которых может начинаться запрос
	&Analyzer::AnaliseCreateTable,	// здесь собраны все специализированные методы для каждого типа запроса
	&Analyzer::AnaliseAlterTable,
	&Analyzer::AnaliseDropTable
};
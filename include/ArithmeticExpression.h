#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "stack.h"

using namespace std;

// Класс для представления арифметического выражения
class Expression {
private:
	string infix;           // Входное инфиксное выражение
	vector<string> postfix; // Постфиксное представление выражения
	vector<string> expr;    // Общий список элементов выражения (лексем)
	vector<char> lexems;    // Список отдельных символов выражения
	vector<string> operands;// Список операндов (чисел)
	map<string, int> priority; // Словарь приоритетов операторов
	
	
public:
	Expression(string inf);
	void Parse();
	bool LexicalCheck();
	bool SyntaxCheck();
	void ToPosfix();
	string GetInfix() const{
		return infix;
	}
	vector<string> GetPosfix() const {
		return postfix;
	}
	double Calculate();
};
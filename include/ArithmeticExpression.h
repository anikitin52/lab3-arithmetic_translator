#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "stack.h"

using namespace std;

class Expression {
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, int> priority;

	void Parse();
	void ToPosfix();
public:
	Expression(string inf);

	string GetInfix() const {
		return infix;
	}
	string GetPosfix() const {
		return postfix;
	}

	vector<char> GetOperands() const;
	double Calculate(const map<char, double>& values);
};
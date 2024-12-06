#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "stack.h"

using namespace std;

class Expression {
	string infix;
	string postfix;
	vector<char> lexems;
	vector<string> operands;
	map<char, int> priority;

	
	
	void ToPosfix();
public:
	Expression(string inf);

	void Parse();

	string GetInfix() const {
		return infix;
	}
	string GetPosfix() const {
		return postfix;
	}

	vector<char> GetOperands() const;
	double Calculate(const map<char, double>& values);
};
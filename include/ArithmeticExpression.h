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
	vector<string> postfix;
	vector<string> expr;
	vector<char> lexems;
	vector<string> operands;
	map<string, int> priority;
	
	
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
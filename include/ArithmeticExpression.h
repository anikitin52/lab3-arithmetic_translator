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
	Expression(string inf) {
		infix = inf;
	}

	void Parse() {
		vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		vector<char> operators = { '+', '-', '*', '/' };
		string number;
		for (char c : infix) {
			if (std::find(numbers.begin(), numbers.end(), c) != numbers.end() || c == '.') {
				number.push_back(c);
			}
			else {
				operands.push_back(number);
				number = "";
				lexems.push_back(c);
			}
		}
		if (number != "") {
			operands.push_back(number);
		}		
	}

	string GetInfix() const {
		return infix;
	}
	string GetPosfix() const {
		return postfix;
	}

	vector<char> GetOperands() const;
	double Calculate(const map<char, double>& values);
};
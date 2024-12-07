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
	
	void ToPosfix();
public:
	Expression(string inf) {
		infix = inf;
	}

	void Parse() {
		// –азбиение строки на операторы и операнды
		vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
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

	bool LexicalCheck() {
		enum class State {
			START,
			FIRST_NUMBER,
			SECOND_NUMBER,
			OTHER
		};

		vector<char> operators = { '+', '-', '*', '/', '(', ')'};
		vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

		for (string number : operands) {
			State status = State::START;
			for (int i = 0; i < number.size(); i++) {
				switch (status) {
				case State::START:
					if (std::find(numbers.begin()+1, numbers.end(), number[i]) != numbers.end()) {
						status = State::FIRST_NUMBER;
					}
					else {
						status = State::OTHER;
					}
					break;
				case State::FIRST_NUMBER:
					if (std::find(numbers.begin(), numbers.end(), number[i]) != numbers.end()) {
						status = State::FIRST_NUMBER;
					}
					else if (number[i] == '.') {
						status = State::SECOND_NUMBER;
					}
					else {
						status = State::OTHER;
					}
					break;
				case State::SECOND_NUMBER:
					if (std::find(numbers.begin(), numbers.end(), number[i]) != numbers.end()) {
						status = State::SECOND_NUMBER;
					}
					else {
						status = State::OTHER;
					}
					break;
				default:
					
					break;
				}
			}
			if (status == State::OTHER) {
				return false;
			}
		}
		return true;
		
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
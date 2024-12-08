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
	vector<string> expr;
	vector<char> lexems;
	vector<string> operands;
	
	void ToPosfix();
public:
	Expression(string inf) {
		infix = inf;
	}

	void Parse() {
		// Разбиение строки на операторы и операнды
		vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		string number;
		for (char c : infix) {
			if (std::find(numbers.begin(), numbers.end(), c) != numbers.end() || c == '.') {
				number.push_back(c);
			}
			else {
				operands.push_back(number);
				expr.push_back(number);
				number = "";
				lexems.push_back(c);
				expr.push_back(std::string(1, c));
			}
		}
		if (number != "") {
			operands.push_back(number);
			expr.push_back(number);
		}	

		for (string number : operands) {
			cout << number << " ";
		}
		cout << "\n";
		for (char lex : lexems) {
			cout << lex;
		}
		cout << "\n";
		for (string ex : expr) {
			cout << ex << "_";
		}
		cout << "\n";


	}

	bool LexicalCheck() {
		enum class State {
			START,
			FIRST_NUMBER,
			SECOND_NUMBER,
			OTHER
		};

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

	bool SyntaxCheck() {
		enum class State {
			S0,
			S1,
			S2,
			ERROR,
			SUCCESS
		};
		
		int k = 0; // Количество скобок
		vector<string> operators = { "+", "-", "*", "/"};
		
		State status = State::S0;
		for (int i = 0; i < expr.size(); i++) {
			switch (status) {

			case State::S0:
				if (expr[i] == "(") {
					k++;
					status = State::S0;
				}
				else if (std::find(operands.begin(), operands.end(), expr[i]) != operands.end()) {
					status = State::S1;
				}
				else if (expr[i][0] == '\0') {
					status = State::S2;
				}
				else {
					status = State::ERROR;
				}
				break;

			case State::S1:
				if (std::find(operators.begin(), operators.end(), expr[i]) != operators.end()) {
					status = State::S0;
				}
				else if (expr[i] == ")") {
					k--;
					if (k >= 0) {
						status = State::S1;
					}
					else {
						status = State::ERROR;
					}
				}
				else if (expr[i][0] == '\0') {
					status = State::S2;
				}
				else {
					status = State::ERROR;
				}
				break;

			case State::S2:
				if (k == 0) {
					status = State::SUCCESS;
				}
				else {
					status = State::ERROR;
				}
			}
			
		}
		if (status == State::ERROR) {
			return false;
		}
		if (status == State::SUCCESS) {
			return true;
		}
		return true;
	}

	string GetInfix() const{
		return infix;
	}
	string GetPosfix() const {
		return postfix;
	}

	vector<char> GetOperands() const;
	double Calculate(const map<char, double>& values);
};
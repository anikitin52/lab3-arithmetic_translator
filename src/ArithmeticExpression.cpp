#include "ArithmeticExpression.h"

Expression::Expression(string inf)
{
	infix = inf;
	priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };
}

void Expression::Parse()
{
	// Разбиение строки на операторы и операнды
	vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	string number;
	for (char c : infix) {
		if (std::find(numbers.begin(), numbers.end(), c) != numbers.end() || c == '.') {
			number.push_back(c);
		}
		else {
			if (number != "") {
				operands.push_back(number);
				expr.push_back(number);
			}
			number = "";
			lexems.push_back(c);
			expr.push_back(std::string(1, c));
		}
	}
	if (number != "") {
		operands.push_back(number);
		expr.push_back(number);
	}
}

bool Expression::LexicalCheck()
{
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
				if (std::find(numbers.begin() + 1, numbers.end(), number[i]) != numbers.end()) {
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

bool Expression::SyntaxCheck()
{
	enum class State {
		S0,
		S1,
		S2,
		ERROR,
		SUCCESS
	};

	int k = 0; // Количество скобок
	vector<string> operators = { "+", "-", "*", "/" };

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

void Expression::ToPosfix()
{
	Stack<string> st;
	vector<string> operators = { "+", "-", "*", "/" };

	for (string lexem : expr) {
		if (std::find(operands.begin(), operands.end(), lexem) != operands.end()) {
			postfix.push_back(lexem);
		}
		else if (lexem == "(") {
			st.push(lexem);
		}
		else if (lexem == ")") {
			while (st.top() != "(") {
				string top_elem = st.top();
				st.pop();
				postfix.push_back(top_elem);
			}
			st.pop();
		}
		else if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
			while (!st.empty() && priority[lexem] <= priority[st.top()]) {
				string top_elem = st.top();
				st.pop();
				postfix.push_back(top_elem);
			}
			st.push(lexem);
		}
	}
	while (!st.empty()) {
		string top_elem = st.top();
		st.pop();
		postfix.push_back(top_elem);
	}
}

double Expression::Calculate()
{
	Parse();
	if (!LexicalCheck()) {
		cout << "Лексическая ошибка!\n";
		return 0;
	}
	if (!SyntaxCheck()) {
		cout << "Синтаксическая ошибка!\n";
		return 0;
	}
	ToPosfix();

	vector<string> operators = { "+", "-", "*", "/" };

	double res;
	Stack<double> st;
	for (string lexem : postfix) {
		if (std::find(operands.begin(), operands.end(), lexem) != operands.end()) {
			st.push(stod(lexem));
		}
		if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
			double top_element, second_element;
			top_element = st.top();
			st.pop();
			second_element = st.top();
			st.pop();

			int current_res{};

			if (lexem == "+") {
				current_res = top_element + second_element;
			}
			if (lexem == "-") {
				current_res = top_element - second_element;
			}
			if (lexem == "*") {
				current_res = top_element * second_element;
			}
			if (lexem == "/") {
				if (second_element == 0) {
					cout << "Ошибка! Деление на 0!";
					return 0.0;
				}
				current_res = top_element / second_element;
			}

			st.push(current_res);
		}
	}
	res = st.top();
	return res;
}

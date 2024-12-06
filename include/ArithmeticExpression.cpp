#include "ArithmeticExpression.h"

Expression::Expression(string inf)
{
	infix = inf;
}
void Expression::ToPosfix()
{
}


void Expression::Parse()
{
	{
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
	}
}

vector<char> Expression::GetOperands() const
{
	return vector<char>();
}

double Expression::Calculate(const map<char, double>& values)
{
	Parse();
	return 0.0;
}

#include "ArithmeticExpression.h"
#include "ArithmeticExpression.h"


void Expression::ToPosfix()
{
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

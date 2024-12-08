#include <iostream>
#include <clocale>
#include "ArithmeticExpression.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметичское выражение" << "\n";
	string input;
	getline(cin, input);
	
	Expression expr(input);
	
	expr.Parse();

	cout << expr.SyntaxCheck();
	

	

	return 0;
}
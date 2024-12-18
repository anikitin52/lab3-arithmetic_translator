﻿#include <iostream>
#include <clocale>
#include "ArithmeticExpression.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Программа Арифметический транслятор предназначена для перевода \nарифметических выражений из инфиксной формы записи в постфиксную форму и \nпоследующего вычисления результатов. Программа поддерживает базовые \nматематические операции сложения (+), вычитания (-), умножения (*) и деления (/).\n\n";
	cout << "ИНСТРУКЦИЯ ПО ИСПОЛЬЗОВАНИЮ \n1. Запустите программу \n2. Введите арифметическое выражение без пробелов \n3. Нажмите Enter для получения результата\n4. Чтобы выйти из программы введите <exit>\n\n";

	cout << "\n\nВведите арифметическое выражение: ";
	string input;
	getline(cin, input);

	while (input != "exit") {
		Expression expr(input);
		cout << "\nРезультат: " << expr.Calculate() << "\n\n";
		cout << "\n\nВведите арифметическое выражение: ";
		getline(cin, input);
	}

	return 0;
}
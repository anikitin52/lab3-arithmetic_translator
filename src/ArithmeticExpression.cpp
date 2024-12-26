#include "ArithmeticExpression.h"

// Конструктор класса Expression, принимающий строку инфиксного выражения
Expression::Expression(string inf)
{
    // Сохраняем входную строку в переменную infix
    infix = inf;
    // Создаем словарь приоритетов операторов
    priority = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2} };
}
// Метод для разбора строки на отдельные лексемы (операторы и операнды)
void Expression::Parse()
{
    // Массив допустимых символов для чисел
    vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    string number; // Переменная для хранения текущего числа
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
    // Если после цикла осталось непустое число, добавляем его в списки
    if (number != "") {
        operands.push_back(number);
        expr.push_back(number);
    }
}
// Метод для проверки корректности записи чисел
bool Expression::LexicalCheck()
{
    // Перечисление возможных состояний при разборе числа
    enum class State {
        START,       // Начальное состояние
        FIRST_NUMBER,// Первая цифра числа
        SECOND_NUMBER,// Вторая часть числа после точки
        OTHER        // Некорректный символ
    };
    vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    // Конечный автомат
    for (string number : operands) {
        State status = State::START; // Начинаем проверку каждого числа с начального состояния
        for (int i = 0; i < number.size(); i++) {
            switch (status) {
            case State::START:
                if (std::find(numbers.begin(), numbers.end(), number[i]) != numbers.end()) {
                    status = State::FIRST_NUMBER;
                }
                else {
                    status = State::OTHER;
                }
                break;
            case State::FIRST_NUMBER:
                // Проверка цифр до точки
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
                // Проверка цифр после точки
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
        // Если в числе обнаружен неправильный символ, возвращаем false
        if (status == State::OTHER) {
            return false;
        }
    }
    // Все числа проверены успешно
    return true;
}
// Метод для проверки синтаксической правильности выражения
bool Expression::SyntaxCheck()
{
    enum class State {
        S0,          // Ждем операнд
        S1,          // Ждем оператор
        S2,          // Все хорошо, но не точно
        ERROR,       // Ошибка
        SUCCESS      // Успешная проверка
    };
    int k = 0; // Количество скобок
    vector<string> operators = { "+", "-", "*", "/" }; // Список допустимых операторов
    // Конечный автомат
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
// Метод преобразования выражения из инфиксной формы в постфиксную
void Expression::ToPosfix()
{
    Stack<string> st; // Стек для хранения операторов
    vector<string> operators = { "+", "-", "*", "/" }; // Допустимые операторы
    for (string lexem : expr) {
        if (std::find(operands.begin(), operands.end(), lexem) != operands.end()) {
            // Если это операнд, сразу добавляем его в постфиксное выражение
            postfix.push_back(lexem);
        }
        else if (lexem == "(") {
            // Открывающую скобку помещаем в стек
            st.push(lexem);
        }
        else if (lexem == ")") {
            // Открывающую скобку помещаем в стек
            while (st.top() != "(") {
                string top_elem = st.top();
                st.pop();
                postfix.push_back(top_elem);
            }
            st.pop();
        }
        else if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
            // Для операторов сравниваем приоритеты
            while (!st.empty() && priority[lexem] <= priority[st.top()]) {
                string top_elem = st.top();
                st.pop();
                postfix.push_back(top_elem);
            }
            st.push(lexem); // Помещаем оператор в стек
        }
    }
    // Достаем оставшиеся операторы из стека
    while (!st.empty()) {
        string top_elem = st.top();
        st.pop();
        postfix.push_back(top_elem);
    }
}
double Expression::Calculate()
{
    // Проверка корректности выражения
    Parse();
    if (!LexicalCheck()) {
        cout << "Лексическая ошибка!\n";
        return 0;
    }
    if (!SyntaxCheck()) {
        cout << "Синтаксическая ошибка!\n";
        return 0;
    }
    // Перевод выражения в постфиксную форму
    ToPosfix();
    vector<string> operators = { "+", "-", "*", "/" };
    // Создаем стек для вычислений
    Stack<double> st;
    // Проходим по каждому элементу постфиксного выражения
    for (string lexem : postfix) {
        if (std::find(operands.begin(), operands.end(), lexem) != operands.end()) {
            // Если это операнд, преобразуем его в double и кладём в стек
            st.push(stod(lexem));
        }
        else if (std::find(operators.begin(), operators.end(), lexem) != operators.end()) {
            // Если это оператор, выполняем соответствующую операцию над двумя верхними элементами стека
            double operand2 = st.top();
            st.pop();
            double operand1 = st.top();
            st.pop();
            if (lexem == "+") {
                st.push(operand1 + operand2);
            }
            else if (lexem == "-") {
                st.push(operand1 - operand2);
            }
            else if (lexem == "*") {
                st.push(operand1 * operand2);
            }
            else if (lexem == "/") {
                if (operand2 == 0) { // Проверка деления на 0
                    cout << "Ошибка! Деление на 0!";
                    return 0.0;
                }
                st.push(operand1 / operand2);
            }
        }
    }
    // Возвращаем результат вычисления, который остался в стеке
    return st.top();
}
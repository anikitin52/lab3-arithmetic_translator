#ifndef STACK_H
#define STACK_H 

#include <vector>
template <class T, class Tcont = std::vector<T>>
class Stack {
    Tcont data;
public:
    // Добавление элемента на вершину стека 
    void push(const T& val) {
        data.push_back(val);
    }

    // Удаление элемента с вершины стека 
    void pop() {
        if (empty()) {
            throw "Stack is empty!";
        }
        data.pop_back();
        
    }

    // Элемент на вершине стека
    T top() {
        if (empty()) {
            throw "Stack is empty!";
        }
        T res = data.back();
        return res;
    }

    // Проверка на пустоту
    bool empty() {
        return data.empty();
    }

    // Размер стека 
    size_t size() {
        return data.size();
    }
};

#endif STACK_H
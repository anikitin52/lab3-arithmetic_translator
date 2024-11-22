#ifndef STACK_H
#define STACK_H 

#include <vector>
template <class T, class Tcont = std::vector<T>>
class Stack {
    Tcont data;
public:
    void push(const T& val) {
        data.push_back(val);
    }

    void pop() {
        if (!empty()) {
            data.pop_back();
        }
    }

    T top() {
        T res = data.back();
        return res;
    }

    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }
};

#endif STACK_H
template <class T, template<class> class Tcont>
class Stack {
    Tcont<T> data;
public:
    void push(const T& val) {
        data.push_back(val);
    }

    void pop() {
        if (!empty()) {
            data.pop_back();
        }
    }

    T& pop() {
        T ret = data.back();
        data.pop_back();
        return ret;
    }

    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }
};
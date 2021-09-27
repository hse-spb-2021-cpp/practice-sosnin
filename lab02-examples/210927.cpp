#include <iostream>

struct OpenObject {
    int a;

    // Если убрать & у возвращаемого значения, то будет создаваться копия
    // которая при передаче в строке 66 превратится в висячую ссылку
    OpenObject &operator=(const OpenObject &other) {
        a = other.a;
        return *this;
    }
};

class ClosedObject {
    friend int square(ClosedObject &obj);

public:
    ClosedObject() {
        a = 2;
    }

    ClosedObject(int _a) : a(_a) {
        b = new int(3);
    }

    ~ClosedObject() {
        if (b) {
            delete b;
        }
    }

private:
    int a;
    int *b{nullptr};

    // protected:
};

int square(ClosedObject &obj) {
    return obj.a * obj.a;
}

int square(OpenObject &obj) {
    return obj.a * obj.a;
}

void abc(float *ptr) {
    if (ptr) {
        std::cout << *ptr << std::endl;
    }
}

void abc(int value) {
    std::cout << value << std::endl;
}

int main() {
    OpenObject OO;
    OO.a = 42;

    OpenObject OtherO;

    ClosedObject CO;

    std::cout << square(OtherO = OO) << std::endl;
    std::cout << square(OO) << std::endl;
    std::cout << square(CO) << std::endl;

    int a = 7;
    int b = 40;

    int &r = a;
    std::cout << r << " " << a << " " << b << std::endl;  // 7 7 40
    r = b;
    b = 13;
    std::cout << r << " " << a << " " << b << std::endl;  // 40 40 13

    // abc(NULL); // Подходят обе перегрузки abc
    abc(nullptr);  // Подходbn только первая перегрузка
    return 0;
}
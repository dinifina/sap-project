// my first program in C++
#include <iostream>
using namespace std;

namespace first {
    int x = 1;
}

namespace second {
    int x = 2;
}

int main() {
    cout << "Hello world!" << std::endl;
    cout << first::x << std::endl;
    cout << second::x << std::endl;
    return 0;
}
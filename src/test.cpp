#include "aux.h"


int main() {
        matrix a({3,4}, range(1,13));
        matrix b({4,3}, range(1,13));
        std::cout << a << std::endl;       
        std::cout << b << std::endl;       
        
        matrix c = a * b;
        std::cout << c << std::endl;
        matrix d = b * a;
        std::cout << d << std::endl;
        return 0;
}

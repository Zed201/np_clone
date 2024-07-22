#include "aux.h"


int main() {
        matrix a({3,4}, range(1,13));
        matrix b({4,3}, range(1,13));
        std::cout << a << std::endl;       
        std::cout << b << std::endl;
        std::cout << a[{3,5}] << std::endl;
        return 0;
}

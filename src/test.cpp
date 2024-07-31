#include "aux.h"

int main() {
        matrix a({2,3,5,5}, range(1, 151));
        std::cout << a << std::endl;
        for (matrix b : a.divide2d()) {
                std::cout << b << std::endl;
        }
        return 0;
}

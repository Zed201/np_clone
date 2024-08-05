#include "aux.h"

int main() {
        matrix a({2, 3, 5, 5}, range(1, 151));
        std::cout << a << std::endl;
        std::cout << a.slice({2, 2, 4, 4}) << std::endl;

        return 0;
}

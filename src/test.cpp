#include "aux.h"

int main() {
        matrix a({2, 3, 5, 5}, range(1, 151));
        matrix b({2, 3, 5, 5}, range(1, 151));
        std::cout << a * b << std::endl;
        return 0;
}

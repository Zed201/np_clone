#include "aux.h"

int main() {
        matrix a({3, 4}, range(1, 13));
        std::cout << a << std::endl;
        std::cout << a.transpose() << std::endl;
        return 0;
}

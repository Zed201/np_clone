#include "aux.h"
// arquivo para testar a implementação em c++, compila com o cmake

int main() {
        matrix a({5, 5}, range(0, 25));
        a[{4,4}] = -100;
        std::cout << a << std::endl;

        return 0;
}

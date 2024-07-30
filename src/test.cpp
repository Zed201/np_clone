#include "aux.h"

int main() {
        matrix a({5,5}, range(1,26));
        std::cout << a << std::endl;
        std::cout << a.transpose() << std::endl;

        return 0;
}

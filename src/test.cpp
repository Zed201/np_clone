#include "aux.h"

int main() {
        matrix a({3, 4}, range(1, 13));
        // std::cout << a.transpose() << std::endl;
        // proxy<matrix> p(a.elem[2],a);
        // std::cout << a << std::endl;
        // p = 1500;
        // std::cout << a << std::endl;
        std::cout << a << std::endl;
        a[{2,2}] = 12500;
        std::cout << a << std::endl;
        a[{2,3}] = 125001;
        std::cout << a << std::endl;
        return 0;
}

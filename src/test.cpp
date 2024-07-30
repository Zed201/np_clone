#include "aux.h"

int main() {
        matrix a({1,5,1}, range(1,6));
        std::cout << a << std::endl;
        a.divide2d();
        return 0;
}

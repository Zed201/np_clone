#include "aux.h"


int main() {
        matrix a({3,4}, range(1,13));
        matrix b({4,3}, range(1,13));
        std::cout << a << std::endl;       
        // std::cout << b << std::endl;
        std::cout << a[{2,3}] << std::endl;
        //matrix c = a.transpose();
        //std::cout << c << std::endl;
        return 0;
}

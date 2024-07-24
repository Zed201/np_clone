#include "aux.h"


int main() {
        matrix a({4,4}, range(1,13));
        //matrix b({4,3}, range(1,13));
        std::cout << a << std::endl;       
        // std::cout << b << std::endl;
        matrix b = a.transpose();
        std::cout << b << std::endl;
        //matrix c = a.transpose();
        //std::cout << c << std::endl;
        return 0;
}

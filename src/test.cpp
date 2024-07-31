#include "aux.h"

int main() {
        matrix a({5,1}, range(1,6));
        std::cout << a << std::endl;
        for(matrix b : a.divide2d()){
                std::cout << b << std::endl;
        }
        return 0;
}

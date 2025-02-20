#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

int main(){
        matrix m({2,2,2}, range(0, 8));
        std::cout << m << std::endl;

        return 0;
}
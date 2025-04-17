#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
        matrix m({2, 2}, {1, 2, 3, 4});
        std::cout << m.det() << std::endl;
        std::cout << m.cofatores() << std::endl;
        std::cout << m.invert();
        return 0;
}

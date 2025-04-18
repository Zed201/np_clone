#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
        matrix m1({4, 4}, {2, 1, 3, 1, 1, 0, 1, 1, 0, 2, 1, 0, 0, 1, 2, 3});
        std::cout << m1.det();
        return 0;
}

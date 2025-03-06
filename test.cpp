#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
        matrix m1({4, 4}, {1, 4, 5, 7, 8, 9, 4, 5, 4, 5, 6, 7, 1, 10, 5, 6});
        d_type a = m1.det();
        std::cout << a;
        return 0;
}

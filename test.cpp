#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
        matrix m1({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        d_type a = m1.det();
        return 0;
}

#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
        matrix m({2, 2}, {2, 1, 4, 3});
        std::cout << m.cofatores();
        return 0;
}

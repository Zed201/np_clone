#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

int main(){
        int* p = (int*)malloc(sizeof(int) * 3);
        int* a = (int*)malloc(sizeof(int) * 3);
        p[0] = 2;
        p[1] = 1;
        p[2] = 3;

        a[0] = 1;
        a[1] = 2;
        a[2] = 3;

        std::cout << eqNorderPointer(p, a);
        return 0;
}
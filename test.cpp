#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
        matrix m1({2,2,2}, {1,2,3,4,5,6,7,8,});
        matrix m2({2,2,2}, {1,2,3,4,5,6,7,8,});   
        matrix p = m1 * m2; // {7,10,15,22,67,78,91,106}
        matrix r({2,2,2}, {7,10,15,22,67,78,91,106});
        std::cout << p << std::endl << std::endl;
        std::cout << r << std::endl;
        return 0;
}
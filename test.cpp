#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
        matrix m1({1,2,3,4,5,6,7,8,});
        
        matrix m2 = m1/1;
        std::cout << m2;
        
        return 0;
}
#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
        matrix m1({1,2,2,4,4,4,8,8,});
        
        matrix m2 = m1/5;
        std::cout << m2;
        
        return 0;
}
#include "src/aux.h"
#include "src/matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
        matrix m({2,2,2}, range(0, 8));
        // std::cout << m << std::endl;
        std::vector<matrix> a =  m.divide2d();
        // for (matrix &i : a){
        //         std::cout << i << std::endl << std::endl;
        // }

        print_vec(a);
        vector<int> b = {1,2,3,};
        print_vec(b);
        return 0;
}
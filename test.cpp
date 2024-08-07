#include "src/matrix.h"
#include "src/aux.h"

int main()
{
    int x = 15;
    matrix a({x,x}, range(0,x*x));
    matrix b({x,x}, range(0,x*x));
    // std::cout << a << std::endl;
    // std::cout << b << std::endl;
    matrix c = a * b;
    // std::cout << c << std::endl;
    // std::cout << a * b << std::endl;
    return 0;
}

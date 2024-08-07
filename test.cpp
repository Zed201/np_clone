#include "src/matrix.h"
#include "src/aux.h"

int main()
{
    int x = 5;
    matrix a = full({x,x},2);
    matrix b = full({x,x},2);
    std::cout << a * b << std::endl;
    return 0;
}

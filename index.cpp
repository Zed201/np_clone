#include "src/aux.h"
#include "src/matrix.h"

int main() {

        //  para trocar o tipo de dado para float, int, double ou long vai no defines.h e so troca o define
        std::cout << "Full de 1" << std::endl;
        matrix uns = full({3, 3}, 1);

        std::cout << uns << std::endl;
        int x = 3;
        std::cout << "matrix identidade " << x << std::endl;
        matrix identidade = indetity(x);
        std::cout << identidade << std::endl;

        std::cout << "Matrix com range" << std::endl;
        matrix m1({3, 3}, range(0, 9));
        std::cout << m1 << std::endl;

        std::cout << "Transposta:" << std::endl;
        std::cout << m1.transpose() << std::endl;

        std::cout << "Flatten:" << std::endl;
        print_vec(m1.flatten());

        m1[{2, 2}] = -10000;
        //  testando troca de dados para atualizar o print

        std::cout << "Troca de dados:" << std::endl;
        std::cout << m1 << std::endl;

        int y = 2;
        std::cout << "Pegando apenas o " << y << " indice" << std::endl;
        std::cout << m1.slice({y}) << std::endl;

        std::cout << "Multiplicação de martizes" << std::endl;

        std::cout << "a:" << std::endl;
        matrix a({1, 3}, {3, 1, 3});
        std::cout << a << std::endl;
        std::cout << "b:" << std::endl;
        matrix b({3, 1}, {1, 3, 1});
        std::cout << b << std::endl;
        std::cout << "=" << std::endl;
        std::cout << a * b << std::endl;
        return 0;
}

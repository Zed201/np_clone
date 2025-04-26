#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <iostream>
#include <numeric>
#include <ostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
        //  try doolittle algorithm to LU decomposition
        matrix A({3, 3}, {1, -2, 1, 2, -3, 1, 1, 4, 2});

        //  code
        vector<int> shape = {3, 3};
        int n = 3;
        matrix L_f = full(shape, 0);
        matrix U_f = full(shape, 0);
        //  codando a partir do geeksforgeeks
        //  for (int i = 0; i < n; i++) {
        //         for (int k = i; k < n; k++) {
        //                 double sum = 0;
        //                 for (int j = 0; j < i; j++)
        //                         sum += L_f[{i, j}] * U_f[{j, k}];
        //                 U_f[{i, k}] = A[{i, k}] - sum;
        //         }
        //
        //         L_f[{i, i}] = 1;
        //         for (int k = i; k < n; k++) {
        //                 //  considerando a diagonal igual a 1
        //                 double sum = 0;
        //                 for (int j = 0; j < i; j++) {
        //                         sum += L_f[{k, j}] * U_f[{j, i}];
        //                 }
        //                 L_f[{k, i}] = (A[{k, i}] - sum) / U_f[{i, i}];
        //         }
        //  }

        //  melhorar sugerida pelo claude, melhora de espaco, LU numa mesma matriz, como L tem diagonal
        //  principal igual a 1, entao ele sobrescreve a diagonal principal com o U_r
        //  para calcular o determinante basicamente so multiplica a diagonal
        matrix LU = full(shape, 0);
        for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                        double sum = 0;
                        for (int k = 0; k < i; k++) {
                                sum += LU[{i, k}] * LU[{k, j}];
                        }
                        LU[{i, j}] = A[{i, j}] - sum;
                }
                //  se for 0 ou muito proximo de zero o determinante vai ser 0
                if (fabs(LU[{i, i}]) < 1e-10) {
                        //  det = 0
                }
                for (int j = i + 1; j < n; j++) {
                        double sum = 0;
                        for (int k = 0; k < i; k++) {
                                sum += LU[{j, k}] * LU[{k, i}];
                        }

                        LU[{j, i}] = (A[{j, i}] - sum) / LU[{i, i}];
                }
        }
        double det = 1;
        for (int i = 0; i < n; i++) {
                det *= LU[{i, i}];
        }
        std::cout << "L\n" << LU << det;

        //  std::cout << L_r << "\n*\n" << U_r << std::endl;
        return 0;
}

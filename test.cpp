#include "src/aux.h"
#include "src/defines.h"
#include "src/matrix.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <ostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
        //  teste de decomoposcao qr
        //  Q = matriz ortogonal(inversa = transposta) e R = matriz triangular superior
        //  o mais estável é o algoritmo de triangulação
        //  ortogonal que emprega os refletores de householder
        int n = 3; // linha
        int m = 4; // coluna
        matrix a({m, n}, range(0, n * m));
        matrix R = full({n,n}, 0);
        matrix Q = full({m,n}, 0);

        for (int j = 0; j <= n; j++)
        {
                matrix V = a.get_col(j);
                for (int i = 0; i < j - 1; i++)
                {
                        // dot prod R[{i, j}] = Q.get_col(i) * a.get_col(j);
                        // V = V - R[{i, j}] * Q.get_col(i);
                }
                // R[{j,j}] = euclidian_norm of (V, 2)
                // Q[{:, j}] = 1.0/R[{j,j}] * V
                //implementar referencia para esse Q e dot product
                
        }
        
        return 0;
}


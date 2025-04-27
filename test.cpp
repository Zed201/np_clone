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
        std::chrono::time_point<std::chrono::system_clock> start, end;
        int t = 10;
        matrix T({t, t}, range(0, t * t));
        start = std::chrono::system_clock::now();
        double det = T.det();
        end = std::chrono::system_clock::now();
        std::cout << det;
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "tempo chrono " << elapsed_seconds.count() << "s\n";
        return 0;
}

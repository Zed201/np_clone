#include "src/aux.h"
#include "src/matrix.h"
#include <chrono>

using namespace std::chrono;

int main() {
        int x = 5;
        matrix a({2, 2, x, x}, range(0, x * x));
        matrix b({2, 2, x, x}, range(0, x * x));
        auto start_mul = high_resolution_clock::now();
        matrix c = a * b;
        auto stop_mul = high_resolution_clock::now();
        auto duration_mul = duration_cast<microseconds>(stop_mul - start_mul);

        auto start_p = high_resolution_clock::now();
        std::cout << c << std::endl;
        auto stop_p = high_resolution_clock::now();
        auto duration_p = duration_cast<microseconds>(stop_p - start_p);

        std::cout << "Time taken by multiplication: " << duration_mul.count() << " microseconds" << std::endl;
        std::cout << "Time taken by print: " << duration_p.count() << " microseconds" << std::endl;
        return 0;
}

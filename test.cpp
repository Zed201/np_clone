#include "src/aux.h"
#include "src/matrix.h"

#include <gtest/gtest.h>
/*
        Usando o gtest https://zwarrior.medium.com/install-google-test-framework-gtest-on-ubuntu-20-04-368eb6951b12
        Tutorial https://www.tutorialspoint.com/gtest/index.htm#gtest_features
*/
TEST(DETERMINANTES, N1){
        FAIL();
}
TEST(DETERMINANTES, N2){
        // matrix m1({2,2}, {1,2,3,4}); // det -2
        FAIL();
}
TEST(DETERMINANTES, N3){
        // matrix m1({2,2}, {1,10,-3,-1}); // det 29
        FAIL();
}

TEST(MULTI, N1){
        // implementar para vatores unidimensionais serem apenas multiplicação numero por numero
	FAIL();
}
TEST(MULTI, N2){
        // matrix m1({2,2}, {1,2,3,4});
        // matrix m2({2,2}, {5,6,7,8});                
        // matrix p = m1 * m2; // {19, 22, 43, 50}
	FAIL();
}
TEST(MULTI, N3){
        // matrix m1({3,3}, {1,2,3,4,5,6,7,8,9});
//         // matrix m2({3,3}, {10,11,12,13,14,15,16,17,18});                
//         // matrix p = m1 * m2; // {84, 90, 96, 201, 216, 231, 318, 342, 366}
	FAIL();
}
TEST(MULTI, NN){
        // fazer algum teste igual oque estava antes de matrizes quadimensionais
	FAIL();
} // dimensões maiores

TEST(INVERT, N1){
	FAIL();
}
TEST(INVERT, N2){
	FAIL();
}
TEST(INVERT, N3){
	FAIL();
}

TEST(NORMALIZE, N3){
        // apenas um normalizar de menor, maior...
	FAIL();
}

TEST(AUTOVALORES, N2){
	FAIL();
}
TEST(AUTOVALORES, N3){
	FAIL();
}

TEST(AUTOVETORES, N2){
	FAIL();
}
TEST(AUTOVETORES, N3){
	FAIL();
}

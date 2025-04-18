#include "src/aux.h"
#include "src/matrix.h"
#include <algorithm>
#include <gtest/gtest.h>
/*
        Usando o gtest https://zwarrior.medium.com/install-google-test-framework-gtest-on-ubuntu-20-04-368eb6951b12
        Tutorial https://www.tutorialspoint.com/gtest/index.htm#gtest_features
*/
TEST(DETERMINANTES, N1) {
        matrix m1({3});
        EXPECT_EQ(m1.det(), 3);
}
TEST(DETERMINANTES, N2) {
        matrix m1({2, 2}, {1, 2, 3, 4});  //  det -2
        EXPECT_EQ(m1.det(), -2);
}
TEST(DETERMINANTES, N3) {
        matrix m1({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});  //  det 0
        EXPECT_EQ(m1.det(), 0);
}

TEST(DETERMINANTES, N4) {
        matrix m1({4, 4}, {2, 1, 3, 1, 1, 0, 1, 1, 0, 2, 1, 0, 0, 1, 2, 3});
        EXPECT_EQ(m1.det(), 6);
}

TEST(MULTI, N1) {
        matrix m1({1});
        matrix m2({2});
        matrix p = m1 * m2;  //  {2}
        matrix r({2});
        ASSERT_TRUE(p == r);
}
TEST(MULTI, N2) {
        matrix m1({2, 2}, {1, 2, 3, 4});
        matrix m2({2, 2}, {5, 6, 7, 8});
        matrix p = m1 * m2;  //  {19, 22, 43, 50}
        matrix r({2, 2}, {19, 22, 43, 50});
        ASSERT_TRUE(p == r);
}
TEST(MULTI, N3) {
        matrix m1({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        matrix m2({3, 3}, {10, 11, 12, 13, 14, 15, 16, 17, 18});
        matrix p = m1 * m2;  //  {84, 90, 96, 201, 216, 231, 318, 342, 366}
        matrix r({3, 3}, {84, 90, 96, 201, 216, 231, 318, 342, 366});
        ASSERT_TRUE(p == r);
}

TEST(MULTI, NN) {
        matrix m1({2, 2, 2},
                  {
                          1,
                          2,
                          3,
                          4,
                          5,
                          6,
                          7,
                          8,
                  });
        matrix m2({2, 2, 2},
                  {
                          1,
                          2,
                          3,
                          4,
                          5,
                          6,
                          7,
                          8,
                  });
        matrix p = m1 * m2;  //  {7,10,15,22,67,78,91,106}
        matrix r({2, 2, 2}, {7, 10, 15, 22, 67, 78, 91, 106});
        //  std::cout << m1 << std::endl;
        ASSERT_TRUE(p == r);
}  //  dimensões maiores

TEST(INVERT, N2) {
        matrix m({2, 2}, {1, 2, 3, 4});
        matrix r({2, 2}, {-2, 1, 1.5, -0.5});
        matrix a = m.invert();
        ASSERT_TRUE(r == a);
}
TEST(INVERT, N3) {
        matrix m({3, 3}, {2, -1, 0, -1, 2, -1, 0, -1, 2});
        matrix r({3, 3}, {0.75, 0.5, 0.25, 0.5, 1, 0.5, 0.25, 0.5, 0.75});
        matrix a = m.invert();
        ASSERT_TRUE(r == a);
}

TEST(NORMALIZE, N3) {
        matrix m({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        matrix r({3, 3}, {0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1});
        matrix a = m.normalize();
        ASSERT_TRUE(r == a);
}

TEST(AUTOVALORES, N2) {
        matrix m({2, 2}, {2, 1, 2, 1});
        std::vector<d_type> r1 = {1, 3};
        std::vector<d_type> a = m.autovalores();

        bool e = r1.size() == a.size() && std::all_of(r1.begin(), r1.end(), [&](const d_type &m) {
                         return std::find(a.begin(), a.end(), m) != a.end();
                 });

        ASSERT_TRUE(e);
}

TEST(AUTOVALORES, N3) {
        matrix m({3, 3}, {2, 0, 0, 0, 3, 4, 0, 4, 9});
        //  talvez trocar para um vector
        std::vector<d_type> r1 = {1, 2, 11};
        std::vector<d_type> a = m.autovalores();

        bool e = r1.size() == a.size() && std::all_of(r1.begin(), r1.end(), [&](const d_type &m) {
                         return std::find(a.begin(), a.end(), m) != a.end();
                 });

        ASSERT_TRUE(e);
}

TEST(IGUALDADE, N3) {
        matrix m1({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        matrix m2({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        ASSERT_TRUE(m1 == m2);
}

//  Falta implementar operadores para esses testes funcionarem, com a verificacao
TEST(AUTOVETORES, N2) {
        matrix m({2, 2}, {2, 1, 2, 1});
        //  talvez trocar para um vector
        std::vector<matrix> r1 = {
                matrix({2, 1}, {-1, 1}),
                matrix({2, 1}, {1, 1}),
        };
        std::vector<matrix> a = m.autovetores();
        //  comparacao independete da ordem
        bool e = r1.size() == a.size() && std::all_of(r1.begin(), r1.end(), [&](const matrix &m) {
                         return std::find(a.begin(), a.end(), m) != a.end();
                 });

        ASSERT_TRUE(e);
}

TEST(AUTOVETORES, N3) {
        matrix m({3, 3}, {2, 0, 0, 0, 3, 4, 0, 4, 9});
        //  talvez trocar para um vector
        std::vector<matrix> r1 = {matrix({3, 1}, {0, -2, 1}), matrix({3, 1}, {1, 0, 0}), matrix({3, 1}, {0, 0.5, 1})};
        std::vector<matrix> a = m.autovetores();

        //  comparacao independete da ordem
        bool e = r1.size() == a.size() && std::all_of(r1.begin(), r1.end(), [&](const matrix &m) {
                         return std::find(a.begin(), a.end(), m) != a.end();
                 });

        ASSERT_TRUE(e);
}

#ifndef AUX_H
#define AUX_H

#include <algorithm>
#include <cmath>
#include <format>
#include <initializer_list>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <vector>

#define d_type          int
#define f_precision     3
#define tab_size        1
#define string_lizer(x) #x
#define t_str(x)        string_lizer(x)

struct search_replace {
        std::regex pattern;
        std::string sub_s;
};

static const struct search_replace rep[] = {
        {std::regex("\\]\\["), std::string("]\n [")},
        //  {std::regex("]+"), std::string("]")},
};

void error_print(const char *text);
void error_print(std::string text);
int pow(int x, int y);
float pow(float x, int y);
std::string print_(int x, int max_digs_space);
std::string print_(float x, int max_digs_space);
std::string print_(double x, int max_digs_space);
int dig_qtd(int x);
int dig_qtd(float x);
int dig_qtd(double x);

//  verificar se ta pegando(tem que ter g++
//  versão 13.1)
class matrix {
    public:
        int n_dim, *dim, el_qdt, max_digs_space;
        d_type *elem, max, min;

        std::vector<int> uni_multi(int i);
        std::vector<int> uni_multi(matrix &m, int i);

        int multi_uni(std::vector<int> i);
        int multi_uni(matrix &m, std::vector<int> i);
        int multi_uni(matrix &m,
                      std::initializer_list<int> i);

        bool is_upper_tri(std::vector<int> i);
        bool is_lower_tri(std::vector<int> i);
        bool diagonal_pri(std::vector<int> i);

        //  matrix(std::vector<int> sh,
        //  std::vector<int> el);
        matrix(std::vector<int> sh, std::vector<d_type> el);
        matrix(std::initializer_list<int> shapes,
               std::initializer_list<d_type> elementos);
        matrix(matrix &n);
        matrix(std::initializer_list<d_type> elementos);

        ~matrix();

        std::vector<int> shape();
        void reshape(std::initializer_list<int> n_shape);

        matrix operator+(int y);
        matrix operator-(int y);
        matrix operator*(int y);
        matrix operator/(int y);

        matrix operator/(matrix &y);
        bool operator==(matrix &y);
        matrix operator+(matrix &y);
        matrix operator-(matrix &y);
        matrix operator*(matrix &y);

        d_type &operator[](std::initializer_list<int> n);
        d_type &operator[](std::vector<int> n);
        d_type &operator[](int n);
        d_type &get(std::vector<int> loc);

        void rec_print(int c, int &c_el,
                       std::string &str) const;
        void format_print(std::string &str) const;
        std::string print() const;

        matrix transpose();

        std::vector<d_type> flatten();

        d_type allSum();
        d_type average();
};

std::ostream &operator<<(std::ostream &os, const matrix &m);
//  range inclusivo de ambos os lados, podendo
//  passar o step
template <typename T>
std::vector<d_type> range(T start, T end, T step = 1) {
        std::vector<d_type> tmp;
        if (start > end) {
                for (; start > end; start -= step) {
                        tmp.push_back(
                                static_cast<d_type>(start));
                }
        } else {
                for (; start < end; start += step) {
                        tmp.push_back(start);
                }
        }
        return tmp;
}
//-----------------------------------------------------------------------------------------------------------------------
template <typename T, typename t> T max_(T x, t y) {
        return (x > y) ? x : y;
}

template <typename T, typename t> T min_(T x, t y) {
        return (x < y) ? x : y;
}
#endif

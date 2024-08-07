#ifndef AUX_H
#define AUX_H

#include "defines.h"
#include "matrix.h"
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <regex>
#include <string.h>
#include <vector>

//  usados para o print
struct search_replace {
        std::regex pattern;
        std::string sub_s;
};

static const struct search_replace rep[] = {
        {std::regex("\\]\\["), std::string("]\n [")},
};

//  auxiliares
void error_print(const char *text);
void error_print(std::string text);
int pow(int x, int y);
float pow(float x, int y);

//  auxiliar que print vetor
template <typename T> void print_vec(std::vector<T> n) {
        std::cout << "[ ";
        for (T i : n) {
                std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
}

//  print formatado de cada tipo de dado
std::string print_(int x, int max_digs_space);
std::string print_(float x, int max_digs_space);
std::string print_(double x, int max_digs_space);
std::string print_(long x, int max_digs_space);

//  auxiliar no print com a quantidade de digitios que um dado vai ter
int dig_qtd(int x);
int dig_qtd(float x);
int dig_qtd(double x);
int dig_qtd(long x);

//  auxiliares para tentar imitar o numpy
matrix full(std::vector<int> shape, d_type n);
matrix full(std::initializer_list<int> shape, d_type n);
matrix indetity(int shape);

//  range inclusivo de ambos os lados
template <typename T> std::vector<d_type> range(T start, T end, T step = 1) {
        std::vector<d_type> tmp;
        if (start > end) {
                for (; start > end; start -= step) {
                        tmp.push_back(static_cast<d_type>(start));
                }
        } else {
                for (; start < end; start += step) {
                        tmp.push_back(start);
                }
        }
        return tmp;
}

//  auxiliares so pq sim
template <typename T, typename t> T max_(T x, t y) { return (x > y) ? x : y; }

template <typename T, typename t> T min_(T x, t y) { return (x < y) ? x : y; }
#endif

#ifndef AUX_H
#define AUX_H

#include "defines.h"
#include "matrix.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <initializer_list>
#include <iostream>
#include <regex>
#include <string.h>
#include <vector>

struct search_replace {
        std::regex pattern;
        std::string sub_s;
};

static const struct search_replace rep[] = {
        {std::regex("\\]\\["), std::string("]\n [")},
};

void error_print(const char *text);
void error_print(std::string text);
int pow(int x, int y);
float pow(float x, int y);

std::string print_(int x, int max_digs_space);
std::string print_(float x, int max_digs_space);
std::string print_(double x, int max_digs_space);
std::string print_(long x, int max_digs_space);

template <typename T> void print_vec(std::vector<T> n) {
        std::cout << "[ ";
        for (T i : n) {
                std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
}

int dig_qtd(int x);
int dig_qtd(float x);
int dig_qtd(double x);
int dig_qtd(long x);

matrix full(std::vector<int> shape, d_type n);
matrix full(std::initializer_list<int> shape, d_type n);
matrix indetity(int shape);

//  range inclusivo de ambos os lados, podendo
//  passar o step
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

template <typename T, typename t> T max_(T x, t y) { return (x > y) ? x : y; }

template <typename T, typename t> T min_(T x, t y) { return (x < y) ? x : y; }
#endif

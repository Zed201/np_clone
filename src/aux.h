#ifndef AUX_H
#define AUX_H

#include <iostream>
#include <vector>
#include <format>
#include <initializer_list>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <regex>


void error_print(const char* text);
void error_print(std::string text);
int pow(int x, int y);
float pow(float x, int y);
std::string print_(int x);
std::string print_(float x);

// range inclusivo de ambos os lados, podendo passar o step
template<typename T>
std::vector<T> range(T start, T end, T step = 1){
        std::vector<T> tmp;
        if(start > end){
                for(; start > end; start -= step){
                        tmp.push_back(start);
                }
        } else {
                for(; start < end; start += step){
                        tmp.push_back(start);
                }
        }
        return tmp;
}

template<typename T>
T max_(T x, T y){
        return (x > y) ? x : y;
}

template<typename T>
T min_(T x, T y){
        return (x < y) ? x : y;
}
#endif


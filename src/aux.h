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

struct search_replace{
        std::regex pattern;
        std::string sub_s;
};

static const struct search_replace rep[] = {
        {std::regex("\\]\\["), std::string("]\n [")},
        // {std::regex("]+"), std::string("]")},
};

void error_print(const char* text);
void error_print(std::string text);
int pow(int x, int y);
float pow(float x, int y);
std::string print_(int x);
std::string print_(float x);

#define d_type int
// verificar se ta pegando(tem que ter g++ versão 13.1)
class matrix{
        public:
        int n_dim, *dim, el_qdt; 
        d_type *elem, max, min;

        std::vector<int> uni_multi(int i);
        int multi_uni(std::vector<int> i);
        int multi_uni(matrix &m, std::vector<int> i);
        std::vector<int> uni_multi(matrix &m, int i);

        bool is_upper_tri(std::vector<int> i);
        bool is_lower_tri(std::vector<int> i);
        bool diagonal_pri(std::vector<int> i);

        matrix(std::vector<int> sh, std::vector<d_type> el);
        matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos) 
        : matrix(std::vector<int>(shapes), std::vector<d_type>(elementos));
        matrix(matrix &n) : matrix(n.shape(), n.flatten());
        matrix(std::initializer_list<d_type> elementos) 
        : matrix(std::vector<int>({((int)elementos.size())}), std::vector<d_type>(elementos));

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
        // operator de multiplicação de matrizes

        void rec_print(int c, int &c_el, std::string &str) const;
        friend std::ostream& operator<<(std::ostream& os, const matrix& m);
        void format_print(std::string& str) const;
        std::string print() const;

        matrix transpose();
          
        std::vector<int> flatten();

        d_type allSum();
        d_type average();

};

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


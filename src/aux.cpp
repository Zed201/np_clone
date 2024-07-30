#include "aux.h"

void error_print(const char *text) {
        std::cerr << std::string(text) << std::endl;
        exit(1);
}

void error_print(std::string text) {
        std::cerr << text << std::endl;
        exit(1);
}

int pow(int x, int y) {
        int tmp = 1;
        for (int i = 0; i < y; i++) {
                tmp *= x;
        }
        return tmp;
}

float pow(float x, int y) {
        float tmp = 1.0;
        for (int i = 0; i < y; i++) {
                tmp *= x;
        }
        return tmp;
}

//     ajeitar formatação
std::string print_(int x, int max_digs_space) {
        //     fazer alguma conta de espaços e
        //     formatação para o tamanho do buffer
        std::string tmp;
        for (int i = 0; i < (max_digs_space - dig_qtd(x)) + tab_size; i++) {
                tmp.push_back(' ');
        }
        tmp.append(std::format("{},", x));
        return tmp;
}

std::string print_(float x, int max_digs_space) {
        std::string tmp;
        for (int i = 0; i < (max_digs_space - dig_qtd(x)) + tab_size; i++) {
                tmp.push_back(' ');
        }
        tmp.append(std::format("{0:." t_str(f_precision) "f},", x));
        return tmp;
}

std::string print_(double x, int max_digs_space) {
        std::string tmp;
        for (int i = 0; i < (max_digs_space - dig_qtd(x)) + tab_size; i++) {
                tmp.push_back(' ');
        }
        tmp.append(std::format("{0:." t_str(f_precision) "f},", x));
        return tmp;
}

std::string print_(long x, int max_digs_space) {
        std::string tmp;
        for (int i = 0; i < (max_digs_space - dig_qtd(x)) + tab_size; i++) {
                tmp.push_back(' ');
        }
        tmp.append(std::format("{},", x));
        return tmp;
}

int dig_qtd(int x) { 
        if(!x){
                return 1;
        }
                return static_cast<int>(log10(x)) + 1; }

int dig_qtd(float x) {
        if(!x){
                return 1 + f_precision;
        } return static_cast<int>(log10(static_cast<int>(x))) + 1 + f_precision; }

int dig_qtd(double x) { 
        if(!x){
                return 1 + f_precision;
        }
        return static_cast<int>(log10(static_cast<int>(x))) + 1 + f_precision; }

int dig_qtd(long x) { 
        if(!x){
                return 1;
        }
        return static_cast<int>(log10(x)) + 1; }

matrix full(std::vector<int> shape, d_type n){
        int i = 1;
        for(int j : shape){
                i *= j;
        }
        std::vector<d_type> el(i);
        std::fill(el.begin(), el.end(), n);
        return matrix(shape, el);
}

matrix full(std::initializer_list<int> shape, d_type n){
        return full(std::vector<int>(shape), n);
}

matrix indetity(int shape){
        matrix a = full({shape, shape}, 0);
        for(int i = 0 ; i < shape; i++){
                a[{i,i}] = 1;
        }
        return a;
}
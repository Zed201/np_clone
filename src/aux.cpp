#include "aux.h"
#include "matrix.h"

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
        int qtd = dig_qtd(x);
        for (int i = 0; i < (max_digs_space - qtd) + tab_size; i++) {
                tmp.push_back(' ');
        }
        char *buffer = (char *)malloc(sizeof(char) * qtd);
        snprintf(buffer, qtd + 2, "%d,", x);

        tmp.append(buffer);
        free(buffer);
        return tmp;
}

std::string print_(float x, int max_digs_space) {
        std::string tmp;
        int qtd = dig_qtd(x);
        for (int i = 0; i < (max_digs_space - qtd) + tab_size; i++) {
                tmp.push_back(' ');
        }

        char *buffer = (char *)malloc(sizeof(char) * qtd);
        snprintf(buffer, f_precision + qtd + 1, df_str, x);
        tmp.append(buffer);
        free(buffer);
        return tmp;
}

std::string print_(double x, int max_digs_space) {
        std::string tmp;
        int qtd = dig_qtd(x);
        for (int i = 0; i < (max_digs_space - qtd) + tab_size; i++) {
                tmp.push_back(' ');
        }

        char *buffer = (char *)malloc(sizeof(char) * qtd);
        snprintf(buffer, f_precision + qtd + 1, df_str, x);

        tmp.append(buffer);
        free(buffer);
        return tmp;
}

std::string print_(long x, int max_digs_space) {
        std::string tmp;
        int qtd = dig_qtd(x);
        for (int i = 0; i < (max_digs_space - qtd) + tab_size; i++) {
                tmp.push_back(' ');
        }

        char *buffer = (char *)malloc(sizeof(char) * qtd);
        snprintf(buffer, qtd + 2, "%ld,", x);

        tmp.append(buffer);
        free(buffer);
        return tmp;
}

int dig_qtd(int x) {
        if (x == 0) {
                return 1;
        }
        return static_cast<int>(log10(abs(x))) + 1 + (x > 0 ? 0 : 1);
}

int dig_qtd(float x) {
        if (x == 0) {
                return 1 + f_precision;
        }
        return static_cast<int>(log10(static_cast<int>(abs(x)))) + 1 + f_precision + (x > 0 ? 0 : 1);
}

int dig_qtd(double x) {
        if (x == 0) {
                return 1 + f_precision;
        }
        return static_cast<int>(log10(static_cast<int>(abs(x)))) + 1 + f_precision + (x > 0 ? 0 : 1);
}

int dig_qtd(long x) {
        if (x == 0) {
                return 1;
        }
        return static_cast<int>(log10(abs(x))) + 1 + (x > 0 ? 0 : 1);
}

matrix full(std::vector<int> shape, d_type n) {
        int i = 1;
        for (int j : shape) {
                i *= j;
        }
        std::vector<d_type> el(i);
        std::fill(el.begin(), el.end(), n);
        return matrix(shape, el);
}

matrix full(std::initializer_list<int> shape, d_type n) { return full(std::vector<int>(shape), n); }

matrix indetity(int shape) {
        matrix a = full({shape, shape}, 0);
        for (int i = 0; i < shape; i++) {
                a[{i, i}] = 1;
        }
        return a;
}
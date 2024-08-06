#ifndef MATIX_H
#define MATIX_H

#include "defines.h"
#include <algorithm>
#include <cmath>
#include <format>
#include <initializer_list>
#include <iostream>
#include <regex>
#include <string.h>
#include <vector>

template <class P> class proxy {
    private:
        d_type &ref;
        P &parent;

    public:
        proxy(d_type &r, P &p) : ref(r), parent(p) {}
        proxy &operator=(const d_type i) {
                this->ref = i;
                this->parent.update();
                return *this;
        }

        operator d_type() const { return ref; }

        void operator=(proxy &i) { i.ref = this->ref; }
};

class matrix {
    public:
        int n_dim, *dim, *pesos_dim, el_qdt, max_digs_space;
        d_type *elem, max, min;

        std::vector<int> uni_multi(int i);
        std::vector<int> uni_multi(matrix &m, int i);

        int multi_uni(std::vector<int> i);
        int multi_uni(matrix &m, std::vector<int> i);
        int multi_uni(matrix &m, std::initializer_list<int> i);

        bool is_upper_tri(std::vector<int> i);
        bool is_lower_tri(std::vector<int> i);
        bool diagonal_pri(std::vector<int> i);

        matrix();
        matrix(std::vector<int> sh, std::vector<d_type> el);
        matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos);
        matrix(const matrix &n);
        matrix(std::initializer_list<d_type> elementos);

        ~matrix();

        std::vector<int> shape();
        void reshape(std::initializer_list<int> n_shape);

        matrix operator+(int y);
        matrix operator-(int y);
        matrix operator*(int y);
        matrix operator/(int y);

        matrix &operator=(const matrix &n);
        matrix operator/(matrix &y);
        bool operator==(matrix &y);
        matrix operator+(matrix &y);
        matrix operator-(matrix &y);
        matrix operator*(matrix &y);

        proxy<matrix> operator[](std::initializer_list<int> n);
        proxy<matrix> operator[](std::vector<int> n);
        proxy<matrix> operator[](int n);
        d_type &get(std::vector<int> loc);

        void rec_print(int c, int &c_el, std::string &str) const;
        void format_print(std::string &str) const;
        std::string print() const;

        matrix transpose();

        std::vector<d_type> flatten();

        d_type allSum();
        d_type average();

        void update();

        std::vector<matrix> divide2d();

        //  basicamente para ser oque o [] faz no numpy normalmente, retornar uma matriz que tem os elementos cortados
        //  nao vai ter de x:y ou coisa parecida pois a logica vai ficar complicada, ainda mais de implementar para ser
        //  usada de forma mais fácilo apenas para ser um [] para retornar matrizes
        matrix slice(std::initializer_list<int> n);
        matrix slice(std::vector<int> n);
};

#endif
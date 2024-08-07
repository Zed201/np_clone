#ifndef MATIX_H
#define MATIX_H

#include "defines.h"
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <regex>
#include <string.h>
#include <vector>

//  Proxy para conseguir detectar quando um dado dentro da matrix
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
    private:
        //  dados da matrix
        int n_dim, *dim, *pesos_dim, el_qdt, max_digs_space;
        d_type *elem, max, min;

        //  auxiliares para fazer as correspondências de indices, de n dimensional para unidimensional e vice versa
        std::vector<int> uni_multi(int i);
        std::vector<int> uni_multi(matrix &m, int i);

        int multi_uni(std::vector<int> i);
        int multi_uni(matrix &m, std::vector<int> i);
        int multi_uni(matrix &m, std::initializer_list<int> i);

        //  auxiliar para o operator[]
        d_type &get(std::vector<int> loc);

        //  auxiliar para a multiplicação de matrizes com dimensões maior que 2, usando a lógica do numpy, de dividir
        //  elas em matrizes de 2 dimensões e multiplicar 1 a 1
        std::vector<matrix> divide2d();

        //  auxiliares para o print
        void rec_print(int c, int &c_el, std::string &str) const;
        void format_print(std::string &str) const;

    public:
        //  construtores
        matrix();
        ~matrix();
        matrix(const matrix &n);
        matrix(std::initializer_list<d_type> elementos);      //  matrix x({1,2,3...})
        matrix(std::vector<int> sh, std::vector<d_type> el);  //  matrix x(vector<int> shape, {1,2,3,4...})
        matrix(std::initializer_list<int> shapes,
               std::initializer_list<d_type> elementos);  //  matrix x({x,y...}. {1,2,3,4...})

        //  auxiliares para matrizes 2d para verificar se um elemento esta em determindada posição da matriz
        bool is_upper_tri(std::vector<int> i);
        bool is_lower_tri(std::vector<int> i);
        bool diagonal_pri(std::vector<int> i);

        //  retorna o shape
        std::vector<int> shape();
        //  muda o shape da matriz
        void reshape(std::initializer_list<int> n_shape);

        //  overload de operações com inteiros apenas
        matrix operator+(int y);
        matrix operator-(int y);
        matrix operator*(int y);
        matrix operator/(int y);

        //  overload de operações com outras matrizes
        matrix &operator=(const matrix &n);
        matrix operator/(matrix &y);
        bool operator==(matrix &y);
        matrix operator+(matrix &y);
        matrix operator-(matrix &y);
        matrix operator*(matrix &y);

        //  retorno de apenas um elemento, ela retorna um proxy para conseguir saber quando um dado dentro da matriz
        //  mudou e assim atualizar certos dados como a print, o max, o min...
        proxy<matrix> operator[](std::initializer_list<int> n);  //  pela coordenada
        proxy<matrix> operator[](std::vector<int> n);            //  pela coordenada
        proxy<matrix> operator[](int n);                         //  pelo indice unidmensional

        std::string print() const;  //  retorna a stirng de print

        matrix transpose();  //  retorna a matriz transposta, seguindo a lógica que aparece no numpy

        std::vector<d_type> flatten();  //  retorna a matriz de forma unidimensional

        d_type allSum();
        d_type average();

        //  basicamente para ser oque o [] faz no numpy normalmente, retornar uma matriz que tem os elementos cortados
        //  nao vai ter de x:y ou coisa parecida pois a logica vai ficar complicada, ainda mais de implementar para ser
        //  usada de forma mais fácilo apenas para ser um [] para retornar matrizes
        void update();
        matrix slice(std::initializer_list<int> n);
        matrix slice(std::vector<int> n);
};

//  overload para printar a matriz
std::ostream &operator<<(std::ostream &os, const matrix &m);

#endif
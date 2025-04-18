#include "matrix.h"
#include "aux.h"
#include "defines.h"
#include <cmath>
#include <ostream>
#include <vector>

std::ostream &operator<<(std::ostream &os, const matrix &m) {
        os << m.print();
        return os;
}

bool operator==(const matrix &A, const matrix &B) {
        return eqOrderPointer(A.dim, A.n_dim, B.dim, B.n_dim) &&     //  se as dimensões são iguais
                eqOrderPointer(A.elem, A.el_qdt, B.elem, A.el_qdt);  //  se os elementos são todos iguais
}

matrix::matrix(std::vector<int> sh, std::vector<d_type> el) : max_digs_space(0), pesos_dim_(((int)sh.size()), 1) {
        int tmp = 1, a = 0;
        this->dim = (int *)malloc(sizeof(int) * sh.size());

        for (int i : sh) {
                this->dim[a++] = i;
                tmp *= i;
        }
        if (tmp < static_cast<int>(el.size())) {
                free(this->dim);
                error_print("Tamanho errado");
        }
        this->n_dim = a;
        a = 0;
        this->el_qdt = tmp;

        for (int i = 0; i < this->n_dim; i++) {
                for (int j = i + 1; j < this->n_dim; j++) {
                        this->pesos_dim_[i] *= sh[j];
                }
        }
        this->elem = (d_type *)malloc(sizeof(d_type) * tmp);

        this->max = el[0];
        this->min = el[0];

        for (d_type i : el) {
                this->elem[a++] = i;
                this->max = max_(this->max, i);
                this->min = min_(this->min, i);
                this->max_digs_space = max_(this->max_digs_space, dig_qtd(i));
        }

        if (a < tmp) {
                for (; a < tmp; a++) {
                        this->elem[a] = 0;
                }
                this->max = max_(this->max, 0);
                this->min = min_(this->max, 0);
        }
}
//  construtor padrão sem nd
matrix::matrix() : matrix({0}) {}

matrix::matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos)
        : matrix(std::vector<int>(shapes), std::vector<d_type>(elementos)) {}

//  construtor de copia
matrix::matrix(const matrix &n) {
        this->n_dim = n.n_dim;
        this->dim = (int *)malloc(sizeof(int) * n.n_dim);

        for (int i = 0; i < n.n_dim; i++) {
                this->dim[i] = n.dim[i];
        }

        this->el_qdt = n.el_qdt;
        this->elem = (d_type *)malloc(sizeof(d_type) * n.el_qdt);

        for (int i = 0; i < n.el_qdt; i++) {
                this->elem[i] = n.elem[i];
        }

        this->max = n.max;
        this->min = n.min;
        this->max_digs_space = n.max_digs_space;

        this->pesos_dim_ = std::vector(n.pesos_dim_);
}

matrix::matrix(std::initializer_list<d_type> elementos)
        : matrix(std::vector<int>({((int)elementos.size())}), std::vector<d_type>(elementos)) {}

matrix::~matrix() {
        if (this->dim != nullptr) {
                free(this->dim);
                this->dim = nullptr;
        }
        //  problema no pesos dim, alguma coisa de free(ta dando um free a mais)
        //  if(this->pesos_dim != nullptr && this->pesos_dim != NULL){
        //          free(this->pesos_dim); // com o exemplo do codigo de test.cpp ele
        //               ele vai nesse free 4 vezes, 1 para o a, 1 para o b, 1 para o pre a * b e 1 para o c
        //               ja verifiquei os numeros(endereços) dos ponteiros e todos são diferentes
        //               mas mesmo assim ele da erro de aparente double free, a mensagem(tem muitos significados)
        //               mas no arch ela não tava dando erro, so aqui no ubuntu
        //          this->pesos_dim = nullptr;
        //  }
        if (this->elem != nullptr) {
                free(this->elem);
                this->elem = nullptr;
        }
}

std::vector<int> matrix::shape() {
        std::vector<int> tmp(this->n_dim);
        for (int i = 0; i < this->n_dim; i++) {
                tmp[i] = this->dim[i];
        }
        return tmp;
}

void matrix::reshape(std::initializer_list<int> n_shape) {
        std::vector<int> n(n_shape);

        int tmp = 1;
        for (int i : n) {
                tmp *= i;
        }

        if (tmp != this->el_qdt) {
                error_print("Erro ao trocar shape");
        }

        if (static_cast<int>(n.size()) != this->n_dim) {
                this->n_dim = n.size();
                this->dim = (int *)std::realloc(this->dim, sizeof(int) * this->n_dim);
        }

        tmp = 0;
        for (int i : n) {
                this->dim[tmp++] = i;
        }
}

matrix &matrix::operator=(const matrix &n) {

        this->max = n.max;
        this->min = n.min;
        this->max_digs_space = n.max_digs_space;

        if (this->elem != nullptr) {
                free(this->elem);
                this->elem = nullptr;
        }

        if (this->dim != nullptr) {
                free(this->dim);
                this->dim = nullptr;
        }

        this->n_dim = n.n_dim;
        this->dim = (int *)malloc(sizeof(int) * n.n_dim);
        for (int i = 0; i < n.n_dim; i++) {
                this->dim[i] = n.dim[i];
        }

        //  estava dando erro no valgrind por nao ter isso, mesmo nao mostrando erro em outro lugar
        this->pesos_dim_ = std::vector<int>(this->n_dim);

        for (int i = 0; i < this->n_dim; i++) {
                this->pesos_dim_[i] = 1;
                for (int j = i + 1; j < this->n_dim; j++) {
                        this->pesos_dim_[i] *= this->dim[j];
                }
        }

        this->elem = (d_type *)malloc(sizeof(d_type) * n.el_qdt);
        this->el_qdt = n.el_qdt;
        for (int i = 0; i < n.el_qdt; i++) {
                this->elem[i] = n.elem[i];
        }

        return *this;
}

matrix matrix::operator+(int y) {
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) + y;
        }
        return matrix(this->shape(), x);
}

matrix matrix::operator-(int y) {
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) - y;
        }
        return matrix(this->shape(), x);
}

matrix matrix::operator*(int y) {
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) * y;
        }
        return matrix(this->shape(), x);
}

template <typename T> matrix matrix::operator/(T y) {
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) / y;
        }
        return matrix(this->shape(), x);
}

bool matrix::operator==(matrix &y) {
        if (this->el_qdt != y.el_qdt) {
                return false;
        }
        for (int i = 0; i < this->el_qdt; i++) {
                if (this->operator[](i) != y[i]) {
                        return false;
                }
        }
        return true;
}

matrix matrix::operator+(matrix &y) {
        if (this->shape() != y.shape()) {
                error_print("Erro de formato");
        }
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) + y[i];
        }
        return matrix(this->shape(), x);
}

matrix matrix::operator-(matrix &y) {
        if (this->shape() != y.shape()) {
                error_print("Erro de formato");
        }
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) - y[i];
        }
        return matrix(this->shape(), x);
}

#define THREAD_MULTI 1

matrix matrix::operator*(matrix &y) {  //     tem que ter referencia pois se não da erro nos destrutores
        if (this->n_dim != y.n_dim) {
                error_print("Erro de dimensões");
        }
        if (this->n_dim == 1 && y.el_qdt == 1 && this->el_qdt == 1) {  //  multiplicacao de matrizes 1x1
                return matrix({this->elem[0] * y.elem[0]});
        }

        if (this->n_dim == 2 && this->dim[1] == y.dim[0]) {  //  matrizes 2d normais
                std::vector<int> sh(2);
                sh[0] = this->dim[0];
                sh[1] = y.dim[1];
                std::vector<d_type> el(this->dim[0] * y.dim[1]);
                matrix m(sh, el);

                for (int i = 0; i < this->dim[0]; i++) {
                        for (int j = 0; j < y.dim[1]; j++) {
                                d_type soma = 0;
                                for (int k = 0; k < this->dim[1]; k++) {
                                        soma += this->operator[]({i, k}) * y[{k, j}];
                                }
                                m[{i, j}] = soma;
                        }
                }
                return m;
        } else if (this->n_dim > 2) {  //  dividr as matrizes em 2d e multiplicar 1 x 1
                                       //  verificar se as dimensões batem
                bool tmp = true;
                for (int i = 0; i < this->n_dim; i++) {
                        if (y.dim[i] != this->dim[i]) {
                                tmp = false;
                        }
                }
                if (!tmp) {
                        error_print("Dimensões diferentes");
                }

                //  A multiplicacao faz por matrizes quadradas separadas
                //  separo as matrizes pelo divide2d e multiplico 1 a 1, em threads diferentes

                std::vector<matrix> a = this->divide2d();
                std::vector<matrix> b = y.divide2d();
                std::vector<matrix> c(a.size());
#if THREAD_MULTI == 1
                std::vector<std::thread> h;
                auto m = [&](matrix &a, matrix &b, matrix &c) { c = (a * b); };
#endif

                for (int i = 0; i < static_cast<int>(c.size()); i++) {
#if THREAD_MULTI == 1
                        std::thread th([&m, i, &a, &b, &c]() { m(a[i], b[i], c[i]); });
                        h.push_back(std::move(th));
#else
                        c[i] = (a[i] * b[i]);
#endif
                }
#if THREAD_MULTI == 1
                for (int i = 0; i < static_cast<int>(c.size()); i++) {
                        h[i].join();
                }
#endif
                //  agora só unir as matrizes do vector
                std::vector<d_type> el(this->el_qdt);
                std::vector<int> sh(this->shape());

                int i = 0;
                for (size_t j = 0; j < c.size(); j++) {
                        for (int k = 0; k < c[j].el_qdt; k++) {
                                el[i++] = c[j].elem[k];
                        }
                }
                return matrix(sh, el);

        } else {
                error_print("Erro nas dimensões");
                return matrix({0});  //  so para nao dar warning
        }
}

d_type &matrix::get(std::vector<int> loc) {
        if (static_cast<int>(loc.size()) != this->n_dim) {
                error_print("Erro de dimensão");
        }
        return this->elem[this->multi_uni(loc)];
}

proxy<matrix> matrix::operator[](int n) {
        if (n >= this->el_qdt) {
                error_print("Acesso indevido");
        }
        return proxy<matrix>(this->elem[n], *this);
}

matrix matrix::slice(std::vector<int> n) {
        if (static_cast<int>(n.size()) == this->n_dim) {
                //  basicamente o mesmo do [] mas encapsulado numa matrix
                return matrix({this->operator[](n)});
        }
        //  basicamente calcular o primeiro e o ultimo elemento a fazer parte do slice
        //  o n ele vai ser o topo e o tmp ele vai ser o base
        std::vector<int> tmp(n);
        std::vector<int> sh;
        for (int i = (int)n.size(); i < this->n_dim; i++) {
                n.emplace_back(this->dim[i] - 1);
                tmp.emplace_back(0);
                sh.emplace_back(this->dim[i]);
        }
        int top = this->multi_uni(n), base = this->multi_uni(tmp);
        std::vector<d_type> el(top - base + 1);
        for (int i = base; i <= top; i++) {
                el[i - base] = this->operator[](i);
        }

        return matrix(sh, el);
}

matrix matrix::slice(std::initializer_list<int> n) { return this->slice(std::vector<int>(n)); }

proxy<matrix> matrix::operator[](std::initializer_list<int> n) {
        return proxy<matrix>(this->get(std::vector<int>(n)), *this);
}

proxy<matrix> matrix::operator[](std::vector<int> n) { return proxy<matrix>(this->get(n), *this); }

matrix matrix::operator/(matrix &y) {
        if (this->shape() != y.shape()) {
                error_print("Erro de formato");
        }
        std::vector<d_type> x(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                x[i] = this->operator[](i) / y[i];
        }
        return matrix(this->shape(), x);
}

//     o const basicamente serve para funcionar
//     junto com o << do cout, basicamente ele
//     indica que a função nao vai modificar o
//     estado da classe, como o operator<< ele é
//     const também, mas ele é de fora, ele
//     deveria ser definido

void matrix::rec_print(int c, int &c_el, std::ostringstream &str) const {
        if (c >= this->n_dim) {
                return;
        }
        //  reduz em muito o tempo do print, pois antes tava usando muito regex
        std::streamsize s = str.tellp();  //  retorna a posição de memoria basicamente o tamanho
                                          //  nao da para acessar o tamanho de um stringstream, entao tem que fazer isso
        std::string p = str.str();
        if (s > 0 && p[s - 1] == ']') {
                //  cont a quantidade de colchetes e add isso menos a quantidade de dimensões, ou espaços
                int c = s;
                while (c >= 0 && p[--c] == ']')
                        ;

                std::string a(this->n_dim - (s - c - 2), ' ');  //  talvez fazer prealocado
                a[0] = '\n';
                str << a;
        }
        str << "[";

        for (int i = 0; i < this->dim[c]; i++) {
                if (c == this->n_dim - 1) {  //  recursão para a dimensão mais interna da matrix
                        str << print_(this->elem[c_el++], this->max_digs_space);
                } else {  //     recursao para as outras dimensões
                        rec_print(c + 1, c_el, str);
                }
        }
        str << "]";
}

std::string matrix::print() const {
        int a = 0;
        std::ostringstream buffer;
        rec_print(0, a, buffer);
        return std::string(buffer.str());
}

matrix matrix::transpose() {
        std::vector<int> d(this->n_dim);
        std::vector<d_type> e(this->el_qdt);
        if (this->n_dim == 1) {  //     se for 1D, so vai
                                 //     retornar ela mesma
                for (int i = 0; i < this->n_dim; i++) {
                        d[i] = this->dim[i];
                }
                for (int i = 0; i < this->el_qdt; i++) {
                        e[i] = this->operator[](i);
                }
        } else if (this->n_dim == 2) {  //  se for 2d quadrada ele so inverter os indíces
                if (this->dim[0] == this->dim[1]) {
                        d[0] = this->dim[1];
                        d[1] = this->dim[0];
                        std::vector<int> tmp(2);

                        for (int i = 0; i < this->el_qdt; i++) {
                                tmp = this->uni_multi(i);
                                if (tmp[0] != tmp[1]) {  //  na diagonal principal nao muda nada
                                        std::swap(tmp[0], tmp[1]);
                                }
                                e[this->multi_uni(tmp)] = this->operator[](i);
                        }
                } else {  //  se não ele cria uma nova matriz e inverte ela
                        int m_dim = max_<int>(this->dim[0], this->dim[1]);
                        std::vector<d_type> t(m_dim *
                                              m_dim);  //     cria um quadrado da maior dimensão
                                                       //  matrix tmp_matrix = full({m_dim, m_dim}, this->min - 1);
                        matrix tmp_matrix({0});
                        for (int i = 0; i < this->el_qdt; i++) {
                                int j = tmp_matrix.multi_uni(this->uni_multi(i));
                                tmp_matrix[j] = this->operator[](i);
                        }
                        matrix tmp_matrix1 = tmp_matrix.transpose();

                        for (int i = 0, j = 0; i < tmp_matrix1.el_qdt; i++) {
                                if (tmp_matrix1[i] != this->min - 1) {
                                        e[j++] = tmp_matrix1[i];
                                }
                        }
                        d[0] = this->dim[1];
                        d[1] = this->dim[0];
                }

        } else {
                error_print("Número de dimensões "
                            "maior que 2, não "
                            "suportado");
        }
        return matrix(d, e);
}

std::vector<d_type> matrix::flatten() {
        std::vector<d_type> t(this->el_qdt);
        for (int i = 0; i < this->el_qdt; i++) {
                t[i] = static_cast<d_type>(this->operator[](i));
        }
        return t;
}

d_type matrix::allSum() {
        d_type t = 0;
        for (int i = 0; i < this->el_qdt; i++) {
                t += this->operator[](i);
        }
        return t;
}

d_type matrix::average() { return (this->allSum() / this->el_qdt); }

void matrix::update() {
        this->max = 0;
        this->min = 0;
        this->max_digs_space = 0;
        for (int i = 0; i < this->el_qdt; i++) {
                this->max = max_(this->max, this->elem[i]);
                this->min = min_(this->min, this->elem[i]);
                this->max_digs_space = max_(this->max_digs_space, dig_qtd(this->elem[i]));
        }
}

//  Retornam com os indices comecamdo em 0
std::vector<int> matrix::uni_multi(int i) {
        std::vector<int> tmp(this->n_dim);
        for (int j = this->n_dim - 1; j >= 0; j--) {
                tmp[j] = i % this->dim[j];
                i /= this->dim[j];
        }
        return tmp;
}

int matrix::multi_uni(std::vector<int> vet) {
        if (static_cast<int>(vet.size()) != this->n_dim) {
                error_print("Erro no numero de dimensões");
        }
        for (int i = 0; i < this->n_dim; i++) {
                if (vet[i] >= this->dim[i]) {
                        error_print("Acesso indevido");
                }
        }
        //  fazer um vetor com os "pesos" de cada dimensão, o quanto vai ter que pular
        //  basicamente a posição i vai ter a multiplicação dos numeros de i + 1 ate o final, o ultimo tendo peso de 1
        int index_tmp = 0;
        for (int i = 0; i < static_cast<int>(vet.size()); i++) {
                index_tmp += (this->pesos_dim_[i] * vet[i]);
        }
        return index_tmp;
}

int matrix::multi_uni(matrix &m, std::vector<int> i) { return m.multi_uni(i); }

int matrix::multi_uni(matrix &m, std::initializer_list<int> i) { return this->multi_uni(m, std::vector<int>(i)); }

std::vector<int> matrix::uni_multi(matrix &m, int i) {
        std::vector<int> tmp(m.n_dim);
        for (int j = m.n_dim - 1; j >= 0; j--) {
                tmp[j] = i % m.dim[j];
                i /= m.dim[j];
        }
        return tmp;
}

bool matrix::is_upper_tri(std::vector<int> i) {
        if (this->n_dim > 2) {
                error_print("Erro de dimensão, só "
                            "pode ser chamado para "
                            "matrizes 2D");
        }
        if (this->multi_uni(i) > this->multi_uni({i[0], i[0]})) {
                return true;
        }
        return false;
}

bool matrix::is_lower_tri(std::vector<int> i) { return !this->is_upper_tri(i); }

bool matrix::diagonal_pri(std::vector<int> i) {
        if (this->n_dim > 2) {
                error_print("Erro de dimensão, só "
                            "pode ser chamado para "
                            "matrizes 2D");
        }
        if (i[0] == i[1]) {
                return true;
        }
        return false;
}

std::vector<matrix> matrix::divide2d() {
        if (this->n_dim <= 2) {
                std::vector<matrix> a(1);
                std::vector<d_type> el(this->el_qdt);
                for (int i = 0; i < this->el_qdt; i++) {
                        el[i] = this->operator[](i);
                }

                a[0] = matrix(this->shape(), el);
                return a;
        }

        int qtd_s = 1;
        for (int i = 0; i < this->n_dim - 2; i++) {
                qtd_s *= this->dim[i];
        }
        std::vector<matrix> a(qtd_s);
        std::vector<int> final_shape = {this->dim[this->n_dim - 2], this->dim[this->n_dim - 1]};
        int tam_2x2 = final_shape[0] * final_shape[1];
        for (int i = 0; i < qtd_s; i++) {
                std::vector<d_type> el(tam_2x2);
                for (int j = 0; j < tam_2x2; j++) {
                        el[j] = this->elem[(i * tam_2x2) + j];
                }
                a[i] = matrix(final_shape, el);
        }
        return a;
}

d_type matrix::det() {
        if (this->el_qdt == 1) {
                return this->elem[0];
        }
        if (this->n_dim > 2 || (this->dim[0] != this->dim[1] && this->n_dim != 1)) {
                error_print("Erro de dimensão");
        }
        if (this->dim[0] == 1 && this->n_dim == 1) {
                return this->elem[0];
        }

        if (this->dim[0] == 2) {
                return (this->elem[0] * this->elem[3]) - (this->elem[1] * this->elem[2]);
        }

        if (this->dim[0] == 3) {
                return ((this->elem[0] * this->elem[4] * this->elem[8]) +
                        (this->elem[1] * this->elem[5] * this->elem[6]) +
                        (this->elem[2] * this->elem[3] * this->elem[7])) -
                        ((this->elem[1] * this->elem[3] * this->elem[8]) +
                         (this->elem[0] * this->elem[5] * this->elem[7]) +
                         (this->elem[2] * this->elem[4] * this->elem[6]));
        }

        d_type det = 0;
        /*
           Tem basicamente as formas de laplace dos cofatores com optimzações de n=2 e n=3,
           basicamente pegar uma linha/coluna e multiplicar pelos cofatores,
           basicamente C_ij = (-1)^{i * j} det(A_ij), onde A_ij e a matrix original sem o ij
           */

        //  usar primeiro a abordagem de criar matrizes recursivamente, depois fazer melhor em questao de memoria
        //  2
        //  for (int idx = 0, i = 0; idx < this->dim[0] * this->dim[0] - 1; idx += this->dim[0], i++) {
        //         //  for percorrenod a primeira coluna, so precia escolher 1 entao o masi facil e assim
        //         //  substituido pelo idx_el, onde ele calcula a matriz de cofator daquele elemento
        //
        //         matrix tmp = full({this->dim[0] - 1, this->dim[0] - 1}, 0);
        //         for (int el = 0, pos = 0; el < this->el_qdt; el++) {  //  TODO: melhorar a soma desse for
        //                 if (el % this->dim[0] != 0 && !(el >= idx && el <= (this->dim[0] + idx - 1))) {
        //                         //  primeira condicao diz respeito a nao estar na mesma coluna
        //                         //  segunda diz respeito a nao estar na mesma linha
        //                         tmp.elem[pos++] = this->elem[el];
        //                 }
        //         }
        //         det += (std::pow(-1, i) * tmp.det() * this->elem[idx]);
        //  }

        //  1
        for (int i = 0; i < this->dim[0]; i++) {
                //  vai so avncando no index da linha, sempre coluna 0
                //  pode trocar mas tem que trocar o index do elemento tambem
                //  mas uma melhora de memoria provavelmente
                //  so teria se ficasse usando apenas referencia, calcular
                //  determinante dessas submatrizes sem criar uma nova, no caso a tmp
                matrix tmp = this->idx_el(i, 0);
                det += (tmp.det() * this->operator[]({i, 0}) * (i % 2 ? -1 : 1));
        }

        //  Comparacao dos resultados do valgrind e hyperfine(tempo de execucao e um det 4x4), sem O1... no compilador:
        //  1:
        //  total heap usage: 135 allocs, 135 frees, 77,656 bytes allocated
        //  1.5ms +- 0.7ms, min 0.9ms -> max 5.9ms
        //
        //  2:
        //  total heap usage: 35 allocs, 35 frees, 76,024 bytes allocated
        //  1.8ms +- 0.8ms, min 1.2ms -> max 6.0ms

        /* todo:
           a outra forma e a de decomposicao lu, em que devemos decompor
           uma matriz em triangular sup e triangular up
           a = l * u =, adicionando a ideia de uma matriz de permutacao inicial,
           para deixar o metodo numericamernte mais estaval (implementar mais tarde)
           */
        return det;
}

matrix matrix::cofatores() {
        if (this->n_dim != 2 || this->dim[0] != this->dim[1]) {  //  apenas para matriz quadrada
                return matrix({0});
        }
        std::vector<d_type> ell;
        for (int idx = 0; idx < this->el_qdt; idx++) {
                std::vector<int> loc = this->uni_multi(idx);
                //  loc[0]->i linha, loc[1]->j coluna
                d_type d = this->idx_el(loc[0], loc[1]).det();
                if (!d) {  //  TODO: algo no print tava colocando -0.000, nao achei o pq ainda
                        ell.emplace_back(d);
                        continue;
                }
                ell.emplace_back(((loc[0] + loc[1]) % 2 ? -1 : 1) * d);
        }
        if (!ell.size()) {
                return matrix({0});
        }
        matrix tmp(this->shape(), ell);
        return tmp;
}

matrix matrix::idx_el(int i, int j) {
        if (this->n_dim > 2) {
                return matrix({0});
        }
        std::vector<int> d = this->shape();
        for (int &i : d) {
                i -= 1;
        }
        std::vector<d_type> els;
        for (int idx = 0; idx < this->el_qdt; idx++) {
                std::vector<int> pos = this->uni_multi(idx);
                //  pos[0] -> linha , pos[1] -> coluna
                if (i != pos[0] && j != pos[1]) {
                        els.emplace_back(this->elem[idx]);
                }
        }
        matrix tmp(d, els);
        return tmp;
}

//  a adjunta e a transposta da de cofatores
matrix matrix::adjunta() { return this->cofatores().transpose(); }

matrix matrix::invert() {
        /*
         * Podemos fazer pela solução analitica A^-1 = 1/det(A) * (Matrix de cofatores)
         *
         * Ou pelo método de Eliminacao de Gaus Jordan
         * */
        d_type det = this->det();
        if (det == 0) {
                return matrix({0});
        }
        return (this->adjunta() / det);
}

//  a'_ij = (a_ij - a_min)/(a_max - a_min)
matrix matrix::normalize() { return (*this - this->min) / (this->max - this->min); }

std::vector<d_type> matrix::autovalores() {
        std::vector<d_type> i;
        i.push_back(1);
        return i;
}
std::vector<matrix> matrix::autovetores() {
        std::vector<matrix> i;
        i.emplace_back(matrix({1}));
        return i;
}

bool matrix::operator<(const matrix &A) const { return this->elem[0] < A.elem[0]; }

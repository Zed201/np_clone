#include "matrix.h"
#include "aux.h"
#include "defines.h"

std::ostream &operator<<(std::ostream &os, const matrix &m) {
        os << m.print();
        return os;
}

matrix::matrix(std::vector<int> sh, std::vector<d_type> el) : max_digs_space(0) {
        int tmp = 1, a = 0;
        this->dim = (int *)malloc(sizeof(int) * sh.size());
        for (int i : sh) {
                this->dim[a++] = i;
                tmp *= i;
        }
        if (tmp < el.size()) {
                free(this->dim);
                error_print("Tamanho errado");
        }
        this->n_dim = a;
        a = 0;
        this->el_qdt = tmp;
        this->pesos_dim = (int *)malloc(sizeof(int) * a);
        for (int i = 0; i < this->n_dim; i++) {
                this->pesos_dim[i] = 1;
                for (int j = i + 1; j < this->n_dim; j++) {
                        this->pesos_dim[i] *= sh[j];
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

        this->max = n.max;
        this->min = n.min;
        this->max_digs_space = n.max_digs_space;

        for (int i = 0; i < n.el_qdt; i++) {
                this->elem[i] = n.elem[i];
        }
}

matrix::matrix(std::initializer_list<d_type> elementos)
        : matrix(std::vector<int>({((int)elementos.size())}), std::vector<d_type>(elementos)) {}

matrix::~matrix() {
        free(this->dim);
        this->dim = nullptr;

        free(this->pesos_dim);
        this->pesos_dim = nullptr;

        free(this->elem);
        this->elem = nullptr;
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

        if (n.size() != this->n_dim) {
                this->n_dim = n.size();
                this->dim = (int *)std::realloc(this->dim, sizeof(int) * this->n_dim);
        }

        tmp = 0;
        for (int i : n) {
                this->dim[tmp++] = i;
        }
}

matrix &matrix::operator=(const matrix &n) {

        if (this->elem != nullptr) {
                free(this->elem);
        }

        if (this->dim != nullptr) {
                free(this->dim);
        }

        this->n_dim = n.n_dim;
        this->dim = (int *)malloc(sizeof(int) * n.n_dim);

        this->el_qdt = n.el_qdt;
        this->elem = (d_type *)malloc(sizeof(d_type) * n.el_qdt);

        this->max = n.max;
        this->min = n.min;
        this->max_digs_space = n.max_digs_space;

        for (int i = 0; i < n.n_dim; i++) {
                this->dim[i] = n.dim[i];
        }

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

matrix matrix::operator/(int y) {
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

matrix matrix::operator*(matrix &y) {  //     tem que ter referencia pois se não da erro nos destrutores
        if (this->n_dim != y.n_dim) {
                error_print("Erro de dimensões");
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

                //  TODO: Optimizar isso daqui
                std::vector<matrix> a = this->divide2d();
                std::vector<matrix> b = y.divide2d();
                std::vector<matrix> c(a.size());
                for (int i = 0; i < c.size(); i++) {
                        for (int j : a[i].shape()) {
                                std::cout << j << " ";
                        }
                        std::cout << std::endl;
                        for (int j : b[i].shape()) {
                                std::cout << j << " ";
                        }
                        std::cout << std::endl;
                        c[i] = (a[i] * b[i]);
                }

                std::vector<d_type> el(this->el_qdt);
                std::vector<int> sh(this->shape());

                int i = 0;
                for (matrix j : c) {
                        for (int k = 0; k < j.el_qdt; k++) {
                                el[i++] = j[k];
                        }
                }
                return matrix(sh, el);

        } else {
                error_print("Erro nas dimensões");
                return matrix({0});  //  so para nao dar warning
        }
}

d_type &matrix::get(std::vector<int> loc) {
        if (loc.size() != this->n_dim) {
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
        if (n.size() == this->n_dim) {
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

matrix matrix::slice(std::initializer_list<int> n) { return this->slice(std::vector(n)); }

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

void matrix::rec_print(int c, int &c_el, std::string &str) const {
        if (c >= this->n_dim) {
                return;
        }
        str.append("[");

        for (int i = 0; i < this->dim[c]; i++) {
                if (c == this->n_dim - 1) {  //     dimensão
                                             //     mais
                                             //     interna
                        str.append(print_(this->elem[c_el++], this->max_digs_space));
                } else {  //     recursao para
                          //     dimensão mais
                          //     interna
                        rec_print(c + 1, c_el, str);
                }
        }
        str.append("]");
}

//  TODO:optimizar isso daqui
void matrix::format_print(std::string &str) const {
        str.append("\n");
        const struct search_replace *t;
        for (t = rep; t < rep + (sizeof(rep) / sizeof(*rep)); t++) {
                str = std::regex_replace(str, t->pattern, t->sub_s);
        }
        std::regex pat("\n ");
        std::string tmp = "\n";
        for (int i = 0; i < this->n_dim - 1; i++) {
                tmp += " ";
        }
        str = std::regex_replace(str, pat, tmp);
        std::regex colchetes(" +\\[{2,}");
        auto beg = std::sregex_iterator(str.begin(), str.end(), colchetes);
        auto end = std::sregex_iterator();
        std::string::const_iterator last_pos = str.begin();
        std::string::const_iterator u = str.end();
        std::string result = "";
        for (std::sregex_iterator i = beg; i != end; ++i) {
                std::smatch m = *i;
                std::string s = m.str();
                int spaces = 0, col = 0;
                for (int j = 0; j < s.size(); j++) {
                        if (s[j] == ' ') {
                                spaces++;
                        } else {
                                col++;
                        }
                }
                spaces = spaces - col + 1;
                tmp = "";
                //  reduz a quantidade de espaços para ficar alinhado
                for (int j = 0; j < spaces; j++) {
                        tmp += " ";
                }
                for (int j = 0; j < col; j++) {
                        tmp += "[";
                }

                result.append(last_pos, m.prefix().second);

                result.append(tmp);

                last_pos = m.suffix().first;
        }
        result.append(last_pos, u);
        str = result;
}

std::string matrix::print() const {
        int a = 0;
        std::string buffer;
        rec_print(0, a, buffer);
        format_print(buffer);
        return buffer;
}

//  TODO: Optimizar isso daqui
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
                        std::vector<d_type> t(m_dim * m_dim);  //     cria um quadrado da maior dimensão
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

std::vector<int> matrix::uni_multi(int i) {
        std::vector<int> tmp(this->n_dim);
        for (int j = this->n_dim - 1; j >= 0; j--) {
                tmp[j] = i % this->dim[j];
                i /= this->dim[j];
        }
        return tmp;
}

int matrix::multi_uni(std::vector<int> vet) {
        if (vet.size() != this->n_dim) {
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
        for (int i = 0; i < vet.size(); i++) {
                index_tmp += (this->pesos_dim[i] * vet[i]);
        }
        return index_tmp;
}

int matrix::multi_uni(matrix &m, std::vector<int> i) { return m.multi_uni(i); }

int matrix::multi_uni(matrix &m, std::initializer_list<int> i) { return this->multi_uni(m, std::vector(i)); }

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

//  dividir em várias matrizes 2d
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
                        int index = (i * tam_2x2) + j;
                        el[j] = this->elem[(i * tam_2x2) + j];
                }
                a[i] = matrix(final_shape, el);
        }
        return a;
}
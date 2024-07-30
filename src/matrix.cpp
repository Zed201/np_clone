#include "aux.h"

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

matrix::matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos)
        : matrix(std::vector<int>(shapes), std::vector<d_type>(elementos)) {}

matrix::matrix(matrix &n) : matrix(n.shape(), n.flatten()) {}

matrix::matrix(std::initializer_list<d_type> elementos)
        : matrix(std::vector<int>({((int)elementos.size())}), std::vector<d_type>(elementos)) {}

matrix::~matrix() {
        free(this->dim);
        free(this->elem);
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

//  TODO: Fazer para matrizes de mais dimensões, basicamente dividir elas em multiplas matrizes 2d e multiplicar elas 1
//  por 1 depois juntar
matrix matrix::operator*(matrix &y) {  //     tem que ter referencia pois se não da erro nos destrutores
        if (this->n_dim != y.n_dim || this->n_dim > 2 || y.n_dim > 2 || this->dim[1] != y.dim[0]) {
                error_print("Erro de dimensões");
        }

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

//     TODO: faze slice para mais elementos nesse
proxy<matrix> matrix::operator[](std::initializer_list<int> n) {
        return proxy<matrix>(this->get(std::vector<int>(n)), *this);
}

proxy<matrix> matrix::operator[](std::vector<int> n) { return proxy<matrix>(this->get(n), *this); }

matrix matrix::operator/(matrix &y) {  //     tem que ter
                                       //     referencia se não ele
                                       //     da erro nos
                                       //     construtores
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

std::ostream &operator<<(std::ostream &os, const matrix &m) {
        os << m.print();
        return os;
}

//     TODO:optimizar isso daqui
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
                // reduz a quantidade de espaços para ficar alinhado
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
        } else if (this->n_dim == 2) {// se for 2d quadrada ele so inverter os indíces 
                if (this->dim[0] == this->dim[1]) { 
                        d[0] = this->dim[1];
                        d[1] = this->dim[0];
                        std::vector<int> tmp(2);

                        for (int i = 0; i < this->el_qdt; i++) {
                                tmp = this->uni_multi(i);
                                if (tmp[0] != tmp[1]) { // na diagonal principal nao muda nada
                                        std::swap(tmp[0], tmp[1]);
                                }
                                e[this->multi_uni(tmp)] = this->operator[](i);
                        }
                } else {// se não ele cria uma nova matriz e inverte ela
                        int m_dim = max_<int>(this->dim[0], this->dim[1]);
                        std::vector<d_type> t(m_dim * m_dim);  //     cria um quadrado da maior dimensão
                        matrix tmp_matrix = full({m_dim, m_dim}, this->min - 1);
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
        int index_tmp = 0;
        int i = 0;
        for (int j = this->n_dim - 1; j != 0; i++, j--) {
                index_tmp += vet[i] * this->dim[j];
        }
        return (index_tmp + vet[i]);
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
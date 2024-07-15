#include "aux.h"

// TODO: Concertar para pegar com template
#define d_type int

public:

        int n_dim = 0, *dim = nullptr, el_qdt = 0; 
        d_type *elem = nullptr, max = 0, min = 0;

        // funções para ajudar a mexer com coordenadas
        std::vector<int> uni_multi(int i){
                std::vector<int> tmp(this->n_dim);
                for(int j = this->n_dim - 1; j >= 0; j--){
                        tmp[j] = i % this->dim[j];
                        i /= this->dim[j];
                }
                return tmp;
        }
        int multi_uni(std::vector<int> i){
                int tmp = 0;
                for(int j = 0; j < this->n_dim - 1; j++){
                        tmp += i[j] * this->dim[j];
                }
                return tmp + i[this->n_dim - 1];
        }
        // sobrecarfas para trabalhar com matrizes diferentes
        int multi_uni(matrix &m, std::vector<int> i){
                int tmp = 0;
                for(int j = 0; j < m.n_dim - 1; j++){
                        tmp += i[j] * m.dim[j];
                }
                return tmp + i[m.n_dim - 1];
        }

        std::vector<int> uni_multi(matrix &m, int i){
                std::vector<int> tmp(m.n_dim);
                for(int j = m.n_dim - 1; j >= 0; j--){
                        tmp[j] = i % m.dim[j];
                        i /= m.dim[j];
                }
                return tmp;
        }

        // funçoes para ver se ta ou noa no triangulo superior ou no inferior da matriz
        bool is_upper_tri(std::vector<int> i){
                if(this->n_dim > 2){
                        error_print("Erro de dimensão, só pode ser chamado para matrizes 2D");
                }
                if(this->multi_uni(i) > this->multi_uni({i[0], i[0]})){
                        return true;
                }
                return false;
        }

        bool is_lower_tri(std::vector<int> i){
                return !this->is_upper_tri(i);
        }

        bool diagonal_pri(std::vector<int> i){
                if(this->n_dim > 2){
                        error_print("Erro de dimensão, só pode ser chamado para matrizes 2D");
                }
                if(i[0] == i[1]){
                        return true;
                }
                return false;
        }

        matrix(std::vector<int> sh, std::vector<d_type> el){
                int tmp = 1, a = 0;
                this->dim = (int *) malloc(sizeof(int) * sh.size()); 
                for(int i : sh){
                        this->dim[a++] = i;
                        tmp *= i;
                }
                if(tmp < el.size()){
                        free(this->dim);
                        error_print("Tamanho errado");
                } 

                this->n_dim = a;
                a = 0;
                this->el_qdt = tmp;
                this->elem = (d_type *)malloc(sizeof(d_type) * tmp);
                this->max = el[0];
                this->min = el[0];
                for(d_type i : el){
                        this->elem[a++] = i;
                        this->max = max_<d_type>(this->max, i);
                        this->min = min_<d_type>(this->min, i);
                }
                if(a < tmp){
                        for(; a < tmp; a++){
                                this->elem[a] = 0;
                        }
                        this->max = max_(this->max, 0);
                        this->min = min_(this->max, 0);
                }
        } 


        matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos) 
        : matrix(std::vector<int>(shapes), std::vector<d_type>(elementos)){} 


        matrix(matrix &n) : matrix(n.shape(), n.flatten()){}

        matrix(std::initializer_list<d_type> elementos) 
        : matrix(std::vector<int>({((int)elementos.size())}), std::vector<d_type>(elementos)){}

        ~matrix(){
                free(this->dim); 
                free(this->elem);
        }

        std::vector<int> shape(){
                std::vector<int> tmp(this->n_dim);
                for(int i = 0; i < this->n_dim; i++){
                        tmp[i] = this->dim[i];
                }
                return tmp;
        } 

        void reshape(std::initializer_list<int> n_shape){
                std::vector n(n_shape);

                int tmp = 1;
                for (int i : n)
                {
                        tmp *= i;
                }

                if(tmp != this->el_qdt){
                        error_print("Erro ao trocar shape");
                }

                if(n.size() != this->n_dim){
                        this->n_dim = n.size();
                        this->dim = (int *) std::realloc(this->dim, sizeof(int) * this->n_dim);
                }

                tmp = 0;
                for(int i : n){
                        this->dim[tmp++] = i;
                }


        }

        matrix operator+(int y){
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] + y;
                }
                return matrix(this->shape(), x);
        }

        matrix operator-(int y){
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] - y;
                }
                return matrix(this->shape(), x);
        }

        matrix operator*(int y){
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] * y;
                }
                return matrix(this->shape(), x);
        }

        matrix operator/(int y){
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] / y;
                }
                return matrix(this->shape(), x);
        }

        bool operator==(matrix &y){
                if(this->el_qdt != y.el_qdt) {
                        return false;
                }
                for(int i = 0; i < this->el_qdt; i++){
                        if(this->elem[i] != y.elem[i]){
                                return false;
                        }
                }
                return true;
        }

        matrix operator+(matrix &y){// tem que ter referencia se não ele da erro nos construtores
                if(this->shape() != y.shape()){
                        error_print("Erro de formato");
                }
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] + y.elem[i];
                }
                return matrix(this->shape(), x);
        }

        matrix operator-(matrix &y){// tem que ter referencia se não ele da erro nos construtores
                if(this->shape() != y.shape()){
                        error_print("Erro de formato");
                }
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] - y.elem[i];
                }
                return matrix(this->shape(), x);
        }

        // TODO: 
        // multiplicação de matrizes normal
        // matrix operator*(matrix &y){// tem que ter referencia se não ele da erro nos construtores
        //         return nullptr;
        // }

        matrix operator/(matrix &y){// tem que ter referencia se não ele da erro nos construtores
                if(this->shape() != y.shape()){
                        error_print("Erro de formato");
                }
                std::vector<int> x(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++) {
                        x[i] = this->elem[i] / y.elem[i];
                }
                return matrix(this->shape(), x);
        }

        // o const basicamente serve para funcionar junto com o << do cout, basicamente ele indica que a função
        // nao vai modificar o estado da classe, como o operator<< ele é const também, mas ele é de fora, ele deveria ser definido
        // fora da classe, mas usando o friend, basicamente podemos definir funções de fora dentro da classe, como não ta usando this ele
        // poderia ser colocada facilmente fora, mas fica mais de boa assim
        void rec_print(int c, int &c_el, std::string &str) const {
                if(c >= this->n_dim){
                        return;
                }
                str.append("[");

                for(int i = 0; i < this->dim[c]; i++){
                        if(c == this->n_dim - 1){// dimensão mais interna 
                                str.append(print_(this->elem[c_el++]));
                        } else {// recursao para dimensão mais interna
                                rec_print(c + 1, c_el, str);
                        }
                }
                str.append("]"); 
        }

        friend std::ostream& operator<<(std::ostream& os, const matrix& m){ 
                os << m.print();
                return os;
        }

        void format_print(std::string& str) const {
                // TODO: usar regex_iterator para printar bonitinho
                str.append("\n");
                const struct search_replace *t;
                for(t = rep; t < rep + (sizeof(rep)/sizeof(*rep)); t++){
                        str = std::regex_replace(str, t->pattern, t->sub_s);
                }
                std::regex pat("\n ");
                std::string tmp = "\n";
                for(int i = 0; i < this->n_dim - 1; i++){
                        tmp += " ";
                }
                str = std::regex_replace(str, pat, tmp);

        }

        std::string print() const {
                int a = 0;
                std::string buffer;
                rec_print(0, a, buffer);
                format_print(buffer);
                return buffer;
        }
        matrix transpose(){
                std::vector<int> d(this->n_dim);
                std::vector<d_type> e(this->el_qdt);

                if(this->n_dim == 1){ // se for 1D, so vai retornar ela mesma
                        for(int i = 0; i < this->n_dim; i++){
                                d[i] = this->dim[i];
                        }
                        for(int i = 0; i < this->el_qdt; i++){
                                e[i] = this->elem[i];
                        }
                } else if(this->n_dim == 2){ // se for diferente de 2d, inverte o shape e os elementos                        
                        if(this->dim[0] == this->dim[1]){ // para matrizes quadradas
                                d[0] = this->dim[1];
                                d[1] = this->dim[0];
                                std::vector<int> tmp(2);

                                for(int i = 0; i < this->el_qdt; i++){
                                        tmp = this->uni_multi(i);
                                        if(tmp[0] != tmp[1]){
                                                // na diagonal principal nao muda nada
                                                std::swap(tmp[0], tmp[1]);
                                        }
                                        e[this->multi_uni(tmp)] = this->elem[i];
                                }
                        } else { // para matrizes nao quadradas TODO
                                int m_dim = max_<int>(this->dim[0], this->dim[1]);
                                std::vector<int> t(m_dim * m_dim); // cria basicamente uma matriz quadrada da maior dimensão
                                std::fill(t.begin(), t.end(), this->min - 1);
                                matrix T({m_dim, m_dim}, t);
                                for(int i = 0; i < this->el_qdt; i++){
                                        T.elem[this->multi_uni(T, this->uni_multi(i))] = this->elem[i];
                                        
                                }

                                for(int i = 0, j = 0; i < T.el_qdt; i++){
                                        if(T.elem[i] != this->min - 1){
                                                e[j++] = T.elem[i];
                                        }
                                }
                                d[0] = this->dim[1];
                                d[1] = this->dim[0];
                        }
                } else {
                        error_print("Número de dimensões maior que 2, não suportado");       
                }
                return matrix(d,e);
        }

        std::vector<int> flatten(){
                std::vector<int> t(this->el_qdt);
                for(int i = 0; i < this->el_qdt; i++){
                        t[i] = this->elem[i];
                }
                return t;
        }

        d_type allSum(){
                d_type t = 0;
                for(int i = 0; i < this->el_qdt; i++){
                        t += this->elem[i];
                }
                return t;
        }

        d_type average(){
                return (this->allSum()/this->el_qdt);
        } 
};


int main() {
        matrix m({3,3,1}, {1,2,3,4,5,6,7,8,9});
        std::cout << m << std::endl;
        // std::cout << m.transpose() << std::endl;
        return 0;
}

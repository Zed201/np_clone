#include <initializer_list>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <regex>
#include "aux.h"

#define d_type int
#define tab_size 2

// reestruturar para ficar mais fácil de chamar no pyx
// trocar para coisas como vector, ou criar sobrecarga para gerar compatibilidade
class matrix{
public:
        int n_dim = 0, *dim = nullptr, el_qdt = 0; 
        d_type *elem = nullptr, max = 0, min = 0;

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

         
        // ver de reduzir isso para apenas 1 construtor, apenas outros para converter (aí implementar o max, min...)
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
                //printf("[");
                str.append("[");

                for(int i = 0; i < this->dim[c]; i++){
                        if(c == this->n_dim - 1){// dimensão mais interna 
                                str.append(print_(this->elem[c_el++]));
                        } else {// recursao para dimensão mais interna
                                rec_print(c + 1, c_el, str);
                        }
                }
                str.append("]");
                // TODO:
                // acertar onde printar o \n, nao consegui decidir bem

        }
        
        friend std::ostream& operator<<(std::ostream& os, const matrix& m){ 
                os << m.print();
                return os;
        }
        std::string print() const {
                int a = 0;
                std::string buffer;
                rec_print(0, a, buffer);
                buffer.append("\n");
                // resolver parcialmente, mas nao fica 100%
                std::regex pattern("\\]\\[");
                std::string sub = "]\n [";

                // std::regex pattern2(" \\[\\[");
                // std::string sub2 = "[[";
                buffer = std::regex_replace(buffer, pattern, sub);
                // buffer = std::regex_replace(buffer, pattern2, sub2);
                return buffer;
        }
        // TODO: Acertar a mudança de eixos
        // basicamente so inverte os eixos, se for 1D ele retorna ela mesmo
        matrix transpose(){
                std::vector<int> d(this->n_dim);
                std::vector<d_type> e(this->el_qdt);
                for(int i = 0; i < this->n_dim; i++){
                        d[i] = this->dim[i];
                }
                for(int i = 0; i < this->el_qdt; i++){
                        e[i] = this->elem[i];
                }
        
                if(this->n_dim == 1){ // se for 1D
                       return matrix(d, e) ;
                } else { // se for diferente de 2d, inverte o shape e os elementos                        
                        // std::reverse(d.begin(), d.end());
                        // std::reverse(e.begin(), e.end()); 
                        return matrix(d, e);
                }
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

/* TODO:
 * -Fazer primeiro toda implementação em cpp para depois portar para .pyx usando os tutotiais de cython
 * -Criar print para 3 dimensões(+-)
 * -Criar outros construtores para ter outras formas de criar, principalmente facilitando a parte do python(tirando tuple, initializer_list...)
 * -Criar o .h referente a isso(O)
 * -Fazer sobre carga para +, -, ==, *(com int,long...), /,(X) 
 * -Ver algoritmo de mutliplicação de matrizes flat(ou dar jeito de transformar)
 * -fazer formula de determinante funcionando para quaisquer dimensões(provavelmente algum algoritmo usando aquela ideia de 1's)
 * -Fazer coisas como matriz transposta(+-)
 * -Fazer o slice por index
 * -Fazer operações como as de allsum, média(X) 
 * -Criar outras funções de auxiliar, como arange...(X)
 *
 * */

int main() {
        // matrix m({3,2,2}, {1,2,3,4,5,6,7,8,9,10,11,12});
        // m.print();
        // std::cout << m.max << std::endl; 
        // std::cout << m.min;

        // std::cout << min_<int>(4,3);
        // std::vector<int> a = range(10, 0, 11);
        // for(int i : a){
                // std::cout << i << std::endl;
        // }
        return 0;
}

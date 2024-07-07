#include <iostream>
#include <initializer_list>
#include <tuple>
#include <vector>
#include "aux.h"

#define d_type int
#define tab_size 2

// reestruturar para ficar mais fácil de chamar no pyx
// trocar para coisas como vector, ou criar sobrecarga para gerar compatibilidade
class matrix{
private:
        int n_dim, *dim = nullptr, el_qdt = 0; 
        d_type *elem = nullptr;

public: 
        matrix(std::initializer_list<int> shapes, std::initializer_list<d_type> elementos){
                std::vector<int> sh(shapes);
                std::vector<d_type> el(elementos);
        
                int tmp = 1, a = 0;
                this->dim = (int *) malloc(sizeof(int) * sh.size()); 
                for(int i : sh){
                        this->dim[a++] = i;
                        tmp *= i;
                }

                if(tmp < elementos.size()){
                        free(this->dim);
                        error_print("Tamanho errado");
                } 

                this->n_dim = a;
                a = 0;
                this->el_qdt = tmp;
                this->elem = (d_type *)malloc(sizeof(d_type) * tmp);

                for(d_type i : el){
                        this->elem[a++] = i;
                }
                if(a < tmp){
                        for(; a < tmp; a++){
                                this->elem[a] = 0;
                        }
                }
        } 


        matrix(std::initializer_list<d_type> elementos) : n_dim(1){
                this->elem = (d_type *) malloc(sizeof(d_type) * elementos.size());
                for (d_type i : elementos)
                {
                        this->elem[this->el_qdt++] = i;
                }
        }

        ~matrix(){
                free(this->dim);
                free(this->elem);
                
        }

        std::vector<int> shape(){
                std::vector<int> tmp(this->n_dim);
                for(int i = 0; i < this->n_dim; i++){
                        tmp.push_back(this->dim[i]);
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
        // TODO: print para 3 dimensoes
        // print para 2 dimensões ta de boa
        void print(){
                // printf("[ ");
                // for (int i = 0; i < this->el_qdt; i++)
                // {
                //         // print de espaço se nao tiver na primeira linha(o 2 é arbitrario para tirar o espaço do [)
                //         int s_jump = (i == 0)? tab_size - 2 : tab_size;

                //         for (int s = 0; s < s_jump; s++)
                //         {
                //                 printf(" ");
                //         }
                //         printf("%d, ", this->elem[i]);
                //         if(this->dim[0] != 0  && (i + 1) % this->dim[0] == 0 && i != this->el_qdt - 1){
                //                 printf("\n");
                //         }
                // }
                // printf("]");
        }
};

/* TODO:
 * -Fazer primeiro toda implementação em cpp para depois portar para .pyx usando os tutotiais de cython
 * -Criar print para 3 dimensões
 * -Criar outros construtores para ter outras formas de criar, principalmente facilitando a parte do python(tirando tuple, initializer_list...)
 * -Criar o .h referente a isso
 * -Fazer sobre carga para +, -, ==, *(com int,long...), /, 
 * -Ver algoritmo de mutliplicação de matrizes flat(ou dar jeito de transformar)
 * -fazer formula de determinante funcionando para quaisquer dimensões(provavelmente algum algoritmo usando aquela ideia de 1's)
 * -Fazer coisas como matriz transposta
 * -Fazer o slice por index
 * -Fazer operações como as de allsum, média 
 * -Criar outras funções de auxiliar, como arange...
 *
 * */

int main() {
        matrix m({3,3}, {1,2,3,4,6,7,8,6,9});
        // m.print();
        return 0;
}

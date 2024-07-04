#include <iostream>
#include <initializer_list>
#include <tuple>
#include <vector>

#define d_type int
#define tab_size 2

class matrix{
    public:
        matrix(std::tuple<int, int, int> dim, std::initializer_list<d_type> elementos) : n_dim(3){
            this->dim[0] = std::get<0>(dim);
            this->dim[1] = std::get<1>(dim);
            this->dim[2] = std::get<2>(dim);

            int a = this->dim[0] * this->dim[1] * this->dim[2];
            this->elem = (d_type *) malloc(sizeof(d_type) * a);
            for (d_type i : elementos)
            {
                   this->elem[this->el_qdt++] = i;
            }
            if(this->el_qdt < a){
                for(int i = el_qdt; i < a; i++){
                    this->elem[i] = 0;
                }
                this->el_qdt = a;
            } else if(this->el_qdt > a){
                std::cerr << "Tamanho errado" << std::endl;
                return;
            }
        }

        matrix(std::tuple<int, int> dim, std::initializer_list<d_type> elementos) : n_dim(2){
            this->dim[0] = std::get<0>(dim);
            this->dim[1] = std::get<1>(dim);

            int a = this->dim[0] * this->dim[1];
            this->elem = (d_type *) malloc(sizeof(d_type) * a);
            for (d_type i : elementos)
            {
                   this->elem[this->el_qdt++] = i;
            }
            if(this->el_qdt < a){
                for(int i = el_qdt; i < a; i++){
                    this->elem[i] = 0;
                }
                this->el_qdt = a;
            } else if(this->el_qdt > a){
                std::cerr << "Tamanho errado" << std::endl;
                return;
            }
        }

        matrix(std::initializer_list<d_type> elementos) : n_dim(1){

            this->elem = (d_type *) malloc(sizeof(d_type) * elementos.size());
            for (d_type i : elementos)
            {
                   this->elem[this->el_qdt++] = i;
            }
        }

        std::tuple<int, int, int> shape(){
            return std::make_tuple(this->dim[0], this->dim[1], this->dim[2]);
        }

        void reshape(std::initializer_list<int> n_shape){
            int tmp = 1;
            for (int i : n_shape)
            {
                tmp *= i;
            }
            if(tmp > this->el_qdt){
                printf("Erro ao trocar de shape\n");
                return;
            }
            std::vector<int> n(n_shape);
            this->dim[0] = n[0];
            this->dim[1] = n[1];
            this->dim[2] = n[2];
        }
        // TODO: print para 3 dimensoes
        // print para 2 dimensões ta de boa
        void print(){
            printf("[ ");
            for (int i = 0; i < this->el_qdt; i++)
            {
                // print de espaço se nao tiver na primeira linha(o 2 é arbitrario para tirar o espaço do [)
                int s_jump = (i == 0)? tab_size - 2 : tab_size;
                
                for (int s = 0; s < s_jump; s++)
                {
                    printf(" ");
                }
                printf("%d, ", this->elem[i]);
                if(this->dim[0] != 0  && (i + 1) % this->dim[0] == 0 && i != this->el_qdt - 1){
                    printf("\n");
                }
            }
            printf("]");
        }
    private:
        int n_dim, dim[3] = {0,0,0}, el_qdt = 0; // largura, altura(para baixo), profundidade
        d_type *elem = nullptr;
};

// int main() {
//     matrix m(std::make_tuple(2,5), {1,2,3,4,6,7,8,6,9, 10});
//     m.print();
//     return 0;
// }
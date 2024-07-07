#include "aux.h"

void error_print(const char* text){
        std::cerr << std::string(text) << std::endl;
        exit(1);
}

void error_print(std::string text){
        std::cerr << text << std::endl;
        exit(1);
}

int pow(int x, int y){
        int tmp = 1;
        for(int i = 0; i < y; i++){
                tmp *= x;
        }
        return tmp;
}

float pow(float x, int y){
        float tmp = 1.0;
        for(int i = 0; i < y; i++){
                tmp *= x;
        }
        return tmp;
}

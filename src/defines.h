#ifndef DEFINES_H
#define DEFINES_H

#define d_type          float
#define f_precision     3   //  precisão quando for usar float ou double
#define tab_size        1   //  tab de distancia
#define string_lizer(x) #x  //  auxiliar para usar os defines no meio de uma string
#define t_str(x)        string_lizer(x)
#define df_str          "%." t_str(f_precision) "f,"  //  string do print de float e double

#endif
#ifndef DEFINES_H
#define DEFINES_H

#define d_type          int
#define f_precision     3
#define tab_size        1
#define string_lizer(x) #x
#define t_str(x)        string_lizer(x)
#define df_str          "%." t_str(f_precision) "f,"
#endif
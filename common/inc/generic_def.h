#include "typedefs.h"
#include "memory_manager.h"

#define CMPR(T, NAME)	e_cmpr NAME(t_gen x, t_gen y)\
					{	\
						e_cmpr ret = eEQUAL;\
						T tmp = (*((T*)(x))) - (*((T*)(y)));\
						if (tmp < 0)	\
							ret = eLESS;\
						else if (tmp > 0)\
							ret = eGREAT;\
						return ret;\
					}


#define ASSGN(T, NAME)	t_gen NAME(T y) \
					{\
						t_gen x = get_mem(1, sizeof(T));\
						*((T*)x) = y;\
						return x;\
					}


#define SWAP(T, NAME)	void NAME(t_gen x, t_gen y) \
					{\
						T tmp = *((T*)x);\
						*((T*)x) = *((T*)y);\
						*((T*)y) = tmp;\
					}
#define FMT_SPF(T) _Generic((T),\
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")
 

#define PRINT_GEN(T, NAME)	void NAME(t_gen x) \
				{ \
					T y;\
					printf(FMT_SPF(y), *((T*)x)); \
				}


/// Below routines defined as reference for basic datatypes
e_cmpr compare_char(t_gen,t_gen);
e_cmpr compare_int(t_gen,t_gen);
e_cmpr compare_float(t_gen,t_gen);
e_cmpr compare_string(t_gen,t_gen);

t_gen assign_char(char);
t_gen assign_int(int);
t_gen assign_float(float);
t_gen assign_string(char*);

void swap_char(t_gen,t_gen);
void swap_int(t_gen,t_gen);
void swap_float(t_gen,t_gen);
void swap_string(t_gen,t_gen);

void print_char(t_gen);
void print_float(t_gen);
void print_int(t_gen);
void print_str(t_gen);

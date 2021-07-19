/*! @file generic_def.h
    @brief 
    Contains Macros that are used for defining psuedo data template functions
*/
#pragma once

#include "typedefs.h"
#include "memory_manager.h"

/// Template Compare function for default data types
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


/// Template Assign memory function for default data types
#define ASSGN(T, NAME)	t_gen NAME(T y) \
					{\
						t_gen x = get_mem(1, sizeof(T));\
						*((T*)x) = y;\
						return x;\
					}


/// Template Swap function for default data types
#define SWAP(T, NAME)	void NAME(t_gen x, t_gen y) \
					{\
						T tmp = *((T*)x);\
						*((T*)x) = *((T*)y);\
						*((T*)y) = tmp;\
					}

/// Defines format specfier depending on type of data
/// used for implementing generic print
/// Note: Requires C11 compiler since it use _Generic 
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
 

/// Template print function for default data types
#define PRINT_GEN(T, NAME)	void NAME(t_gen x) \
				{ \
					T y;\
					printf(FMT_SPF(y), *((T*)x)); \
				}

/// Template function for comparing elemts at given indicies of an array for default data types
#define CMPR_IDX(T, NAME)	e_cmpr NAME(t_gen x, int idx1, int idx2)\
					{	\
						e_cmpr ret = eEQUAL;\
						T *arr = ((T*)(x));\
						T tmp = arr[idx1] -arr[idx2];\
						if (tmp < 0)	\
							ret = eLESS;\
						else if (tmp > 0)\
							ret = eGREAT;\
						return ret;\
					}

/// Template function for swaping elemts at given indicies of an array for default data types
#define SWP_IDX(T, NAME)	void NAME(t_gen x, int idx1, int idx2)\
					{	\
						T *arr = ((T*)(x));\
						T tmp = arr[idx1] ;\
						arr[idx1] = arr[idx2];\
						arr[idx2] = tmp;\
					}

/// Template function for copying element to a given index of an array for default data types
#define COPY_IDX(T, NAME)	void NAME(t_gen x, int idx1, t_gen data)\
					{	\
						T *arr = ((T*)(x));\
						arr[idx1] = *((T*)(data));\
					}

/// Template function for getting element at a given index of an array for default data types
#define GET_IDX(T, NAME)	t_gen NAME(t_gen x, int idx1)\
					{	\
						T *arr = ((T*)(x));\
						t_gen tmp = &arr[idx1] ;\
						return tmp;\
					}

/// Template function for getting element at a given index of an array for default data types
#define GET_IDX_CPY(T, NAME)	t_gen NAME(t_gen x, int idx1)\
					{	\
						T *arr = ((T*)(x));\
						t_gen tmp = get_mem(1, sizeof(T));\
						*(T*)tmp = arr[idx1] ;\
						return tmp;\
					}

/// Below routines defined as reference for basic datatypes
e_cmpr compare_char(t_gen,t_gen);
e_cmpr compare_int(t_gen,t_gen);
e_cmpr compare_float(t_gen,t_gen);
e_cmpr compare_string(t_gen,t_gen);
e_cmpr compare_gen(t_gen,t_gen);

t_gen assign_char(char);
t_gen assign_int(int);
t_gen assign_float(float);
t_gen assign_string(char*);
t_gen assign_gen(t_gen);

void swap_char(t_gen,t_gen);
void swap_int(t_gen,t_gen);
void swap_float(t_gen,t_gen);
void swap_string(t_gen,t_gen);
void swap_gen(t_gen,t_gen);

void print_char(t_gen);
void print_float(t_gen);
void print_int(t_gen);
void print_str(t_gen);
void print_gen(t_gen);

e_cmpr compare_idx_char(t_gen,int,int);
e_cmpr compare_idx_int(t_gen,int,int);
e_cmpr compare_idx_float(t_gen,int,int);

void swap_idx_char(t_gen,int,int);
void swap_idx_int(t_gen,int,int);
void swap_idx_float(t_gen,int,int);

void copy_idx_char(t_gen,int,t_gen);
void copy_idx_int(t_gen,int,t_gen);
void copy_idx_float(t_gen,int,t_gen);

t_gen get_idx_char(t_gen,int);
t_gen get_idx_int(t_gen,int);
t_gen get_idx_float(t_gen,int);

t_gen get_idx_char_cpy(t_gen,int);
t_gen get_idx_int_cpy(t_gen,int);
t_gen get_idx_float_cpy(t_gen,int);

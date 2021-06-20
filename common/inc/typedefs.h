#pragma once
#include <stdbool.h>

/// Typedefing Standard data types
typedef char		t_int8;
typedef unsigned char	t_uint8;
typedef short		t_int16;
typedef unsigned short	t_uint16;
typedef int		t_int32;
typedef unsigned int	t_uint32;
typedef float		t_float;
typedef double		t_double;

/// Enum to create data structure of the following type
typedef enum data_types {
	eINT8,
	eUINT8,
	eINT16,
	eUINT16,
	eINT32,
	eUINT32,
	eFLOAT,
	eDOUBLE,
	eSTRING,
	eGEN,
	eUSER,
}e_data_types;

/// Custom Compare function return type
typedef enum {
	eLESS=-1,
	eEQUAL=0,
	eGREAT=1,
} e_cmpr;

/// Base Data type used for all data structure and data elements
typedef void* t_gen;



/// common routines supported by all data structures
typedef t_gen (*f_gen)(t_gen);
typedef t_gen (*f_gen2)(t_gen, t_gen);
typedef void (*f_vgen)(t_gen);
typedef void (*f_vgen2)(t_gen, t_gen);
typedef t_gen (*f_genidx)(t_gen, int);

typedef bool (*f_empty)(t_gen);
typedef bool (*f_full)(t_gen);
typedef int (*f_len)(t_gen);
typedef f_vgen f_print;

typedef f_vgen2 f_ins;
typedef f_gen2 f_del;
typedef f_gen2 f_find;
typedef f_vgen f_destroy;
typedef f_genidx f_del_idx;
typedef f_genidx f_get_idx;

/// Basic operations required for generic data type support
typedef e_cmpr (*f_cmpr)(t_gen,t_gen);
typedef void(*f_free)(t_gen, char*, int);
typedef f_vgen2 f_assign;
typedef f_vgen2 f_swap;

typedef e_cmpr (*f_cmp_idx)(t_gen,int, int);
typedef void (*f_swp_idx)(t_gen,int, int);
typedef void (*f_cpy_idx)(t_gen,int, t_gen);

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

typedef struct elem {
	t_gen data;
	struct elem *nxt;
	struct elem *prv;
} t_elem;


/// common routines supported by all data structures
typedef void (*f_print)(t_gen);
typedef bool (*f_empty)(t_gen);
typedef bool (*f_full)(t_gen);
typedef int (*f_len)(t_gen);

/// Basic operations required for generic data type support
typedef e_cmpr (*f_cmpr)(t_gen,t_gen);
typedef void (*f_assign)(t_gen,t_gen);
typedef void (*f_swap)(t_gen,t_gen);

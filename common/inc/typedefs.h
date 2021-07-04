/*! @file typedefs.h
    @brief 
    Contains typedefs for all necessary data type and function pointers
*/
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
typedef void* t_gen;	///< Generic data pointer



/// Generic data pointer definitions that are common to most data structure operations
typedef t_gen (*f_gen)(t_gen);			///< fn ptr that takes one gen ptr and return gen ptr
typedef t_gen (*f_gen2)(t_gen, t_gen);		///< fn ptr that takes two gen ptr and return gen ptr
typedef t_gen (*f_gen3)(t_gen, t_gen, t_gen);	///< fn ptr that takes three gen ptr and return gen ptr
typedef void (*f_vgen)(t_gen);			///< fn ptr that takes one gen ptr and return nothing
typedef void (*f_vgen2)(t_gen, t_gen);		///< fn ptr that takes two gen ptr and return nothing
typedef t_gen (*f_genidx)(t_gen, int);		///< fn ptr that takes one gen ptr, idx and return gen ptr

typedef bool (*f_empty)(t_gen);			///< fn type of an empty function
typedef bool (*f_full)(t_gen);			///< fn type of a full function
typedef int (*f_len)(t_gen);			///< fn type of get len function
typedef f_vgen f_print;				///< fn type to print function

typedef f_vgen2 f_ins;				///< fn type of insert elem function
typedef f_gen2 f_del;				///< fn type of delete elem function
typedef f_gen2 f_find;				///< fn type of find a elem function
typedef f_vgen f_destroy;			///< fn type of destroy function
typedef f_genidx f_del_idx;			///< fn type of get elem at idx function
typedef f_genidx f_get_idx;			///< fn type of delete elem at idx function

/// Basic operations required for generic data type support
typedef e_cmpr (*f_cmpr)(t_gen,t_gen);
typedef void(*f_free)(t_gen, char*, int);
typedef f_vgen2 f_assign;
typedef f_vgen2 f_swap;

typedef e_cmpr (*f_cmp_idx)(t_gen,int, int);
typedef void (*f_swp_idx)(t_gen,int, int);
typedef void (*f_cpy_idx)(t_gen,int, t_gen);

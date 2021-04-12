#pragma once

typedef char		t_int8;
typedef unsigned char	t_uint8;
typedef short		t_int16;
typedef unsigned short	t_uint16;
typedef int		t_int32;
typedef unsigned int	t_uint32;
typedef float		t_float;
typedef double		t_double;


typedef enum data_types {
	eINT8,
	eUINT8,
	eINT16,
	eUINT16,
	eINT32,
	eUINT32,
	eFLOAT,
	eDOUBLE,
	eUSER,
}e_data_types;

typedef void* t_gen;

typedef struct elem {
	int data;
	struct elem *nxt;
	struct elem *prv;
} t_elem;



t_elem* get_node(int data);

typedef void (*f_print)(t_gen);
typedef bool (*f_empty)(t_gen);
typedef bool (*f_full)(t_gen);
typedef int (*f_len)(t_gen);

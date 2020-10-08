#pragma once

#define	CAST(X,T)		((T)(X))

#define	GREATER(X, Y, T)		(((T)(X)) >  ((T)(Y)))
#define GREAT_EQUAL(X, Y, T)	(((T)(X)) <= ((T)(Y)))
#define	LESSER(X, Y, T)			(((T)(X)) <  ((T)(Y)))
#define LESS_EQUAL(X, Y, T)		(((T)(X)) <= ((T)(Y)))
#define	EQUAL(X, Y, T)			(((T)(X)) == ((T)(Y)))
#define	NOT_EQUAL(X, Y, T)		(((T)(X)) != ((T)(Y)))


typedef char			t_int8;
typedef unsigned char	t_uint8;
typedef short			t_int16;
typedef unsigned short	t_uint16;
typedef int				t_int32;
typedef unsigned int	t_uint32;
typedef float			t_float;
typedef double			t_double;


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


typedef struct element {
	void *elem;
} t_element;



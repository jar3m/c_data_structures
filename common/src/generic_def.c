#include "common.h"
#include "generic_def.h"

CMPR(char,compare_char)
CMPR(int, compare_int)
CMPR(float, compare_float)


e_cmpr compare_string(t_gen x, t_gen y)
{
	int res = strcmp((char*)x,(char*)y);

	if(res < 0) {
		return eLESS;	
	}
	if(res > 0) {
		return eGREAT;	
	}
	return eEQUAL;	
}

ASSGN(char, assign_char)
ASSGN(int, assign_int)
ASSGN(float, assign_float)

t_gen assign_string(char *x)
{
	t_gen tmp = (t_gen)get_mem(1,strlen(x)+1);

	strcpy(tmp,x);

	return tmp;
}	

SWAP(char, swap_char)
SWAP(int, swap_int)
SWAP(float, swap_float)
SWAP(char*, swap_string)

PRINT_GEN(char, print_char)
PRINT_GEN(int, print_int)
PRINT_GEN(float, print_float)

void print_str(t_gen str)
{
	printf("%s", (char*)str);
}

CMPR_IDX(char,compare_idx_char)
CMPR_IDX(int,compare_idx_int)
CMPR_IDX(float,compare_idx_float)

SWP_IDX(char,swap_idx_char)
SWP_IDX(int,swap_idx_int)
SWP_IDX(float,swap_idx_float)

COPY_IDX(char, copy_idx_char)
COPY_IDX(int, copy_idx_int)
COPY_IDX(float, copy_idx_float)

GET_IDX(char, get_idx_char)
GET_IDX(int, get_idx_int)
GET_IDX(float, get_idx_float)



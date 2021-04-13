#include <string.h>
#include "generic_def.h"

CMPR(char, compare_char)
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

#include "common.h"

void init_data_params(t_dparams *prms, e_data_types data_type)
{
	switch(data_type)
	{
		case eINT8:
			//char list;
			prms->cmpr = compare_char;
			prms->swap = swap_char;
			prms->cmp_idx = compare_idx_char;
			prms->swp_idx = swap_idx_char;
			prms->cpy_idx = copy_idx_char;
			prms->get_idx  = get_idx_char;
			prms->print_data = print_char;
			prms->free = FREE_MEM;
			break;
		case eINT32:
			//int list;
			prms->cmpr = compare_int;
			prms->swap = swap_int;
			prms->cmp_idx = compare_idx_int;
			prms->swp_idx = swap_idx_int;
			prms->cpy_idx = copy_idx_int;
			prms->get_idx  = get_idx_int;
			prms->print_data = print_int;
			prms->free = FREE_MEM;
			break;
		case eFLOAT:
			//float list;
			prms->cmpr = compare_float;
			prms->swap = swap_float;
			prms->cmp_idx = compare_idx_float;
			prms->swp_idx = swap_idx_float;
			prms->cpy_idx = copy_idx_float;
			prms->get_idx  = get_idx_float;
			prms->print_data = print_float;
			prms->free = FREE_MEM;
			break;
		case eSTRING:
			//string list;
			prms->cmpr = compare_string;
			prms->swap = swap_string;
			prms->print_data = print_str;
			prms->free = FREE_MEM;
			break;
#if 0
		case eGEN:
			//gen list;
			prms->cmpr = compare_gen;
			prms->swap = swap_gen;
			break;
#endif
	}
}	



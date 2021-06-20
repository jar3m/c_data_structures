#pragma once

#include "os.h"
#include "typedefs.h"
#include "logger.h"
#include "memory_manager.h"
#include "fault_manager.h"
#include "generic_def.h"

typedef struct params {
	// type of datatypes
	e_data_types type;

	// data type specific routines
	f_cmpr cmpr;
	f_assign assign;
	f_swap swap;
	f_free free;
	f_cmp_idx cmp_idx;
	f_swp_idx swp_idx;
	f_cpy_idx cpy_idx;
	f_get_idx get_idx;
	f_print print_data;
} t_dparams;

void init_data_params(t_dparams*, e_data_types);



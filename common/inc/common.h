/*! @file common.h
    @brief 
    Top level include containg common headers
*/
#pragma once

#include "os.h"
#include "typedefs.h"
#include "logger.h"
#include "memory_manager.h"
#include "fault_manager.h"
#include "generic_def.h"

/*! data params struct to be passed to all data structures
 *  it holds functions pointers for operating on data depending on type of it
 */
/// data params struct defn
typedef struct data_params {
	// type of datatypes
	e_data_types type;		///< Holds elem data type

	// data type specific routines	
	f_cmpr cmpr;			///< Routine used for comparing two given elems of said type
	f_assign assign;		///< Routine used for creating memory for storing the data
	f_swap swap;			///< Routine used for swaping two elemnts of goven data
	f_free free;			///< Routine used for freeing elements of said data
	f_cmp_idx cmp_idx;		///< Routine used for comparing elems in given array indicies
	f_swp_idx swp_idx;              ///< Routine used for swapring elems in given array indicies	
	f_cpy_idx cpy_idx;              ///< Routine used for copying elems in given array indicies
	f_get_idx get_idx;              ///< Routine used for getting elem in given array index
	f_print print_data;		///< Routine used for printing elem data
} t_dparams;

void init_data_params(t_dparams*, e_data_types);



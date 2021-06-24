/*! @file fault_manager.h
    @brief 
    Contains declarations of fault manager routines
*/

#pragma once

#include <os.h>

/// Function pointer for fault handler
typedef void (*f_fault_handle)(int, siginfo_t *, void *);


void fault_manager_init(f_fault_handle h);

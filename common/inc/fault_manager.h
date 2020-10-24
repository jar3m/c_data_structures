#pragma once
#include <os.h>

typedef void (*f_fault_handle)(int,siginfo_t *,void *);


void fault_manager_init(f_fault_handle h);

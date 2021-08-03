/*! @file array.c
    @brief 
    Contains definitions of routines supported by arrays 
*/
#include "array.h"

/*! @brief  
 *  Selection sort is an in-place comparison sorting algorithm. 
 *  It has an O(n2) time complexity
 *  @param a  - Pointer to array
 *  @param n  - size of array
 *  @param op - Data type specific params 
		for operation such as compare and swap
 *  @return   - NA
 * */
void selection_sort(t_gen a, int n, t_dparams *op)
{
	int start_idx, min_idx, idx;

	// Scan segments A[0], A[1], ...
	for (start_idx = 0; start_idx < n; start_idx++) {
		// locate position of min elem in cur segment
		min_idx = start_idx;
		for (idx = min_idx+1; idx < n; idx++) {
			if (op->cmpr_idx(a, idx, min_idx) == eLESS) {
				min_idx = idx;
			}
		}
		// Move minm to start of cur segment
		op->swap_idx(a, start_idx, min_idx);
	}
}

/*! @brief  
 *  Insertion sort builds the final sorted array one item at a time.
 *  It has an O(n2) time complexity
 *  @param a  - Pointer to array
 *  @param n  - size of array
 *  @param op - Data type specific params 
		for operation such as compare and swap
 *  @return   - NA
 * */
void insertion_sort(t_gen a, int n, t_dparams *op)
{
	int pos, nxt_pos;

	// grow longer and longer sorted segments
	for (pos = 1; pos < n; pos++) {
		// In each iter A[0] - A[pos-1] is already sorted
		//Move the first elem after sorted segmen left 
		// till it is in corrext place
		nxt_pos = pos;
		while (nxt_pos > 0 && 
				op->cmpr_idx(a, nxt_pos, nxt_pos - 1) == eLESS) {
			op->swap_idx(a, nxt_pos, nxt_pos - 1);
			nxt_pos -= 1;
		}
	}
}

/*! @brief  
 *  Util function to be used by quick sort for sorting partitions
 *  @param a  - Pointer to array
 *  @param l  - idx to partition start
 *  @param h  - idx to partition end
 *  @param op - Data type specific params 
		for operation such as compare and swap
 *  @return   - index of pivot
 * */
int quick_sort_partition(t_gen a, int lo, int hi, t_dparams *op)
{
	int pivot = hi;
	int green, yellow;

	yellow = lo - 1;
	for (int green = lo; green <= (hi - 1); green++) {
		if (op->cmpr_idx(a, green, pivot) == eLESS) {
			op->swap_idx(a, ++yellow, green);
		}
	}
	op->swap_idx(a, ++yellow, pivot);
 
	return yellow;
}

/*! @brief  
 *  Quicksort is an in-place sorting algorithm
 *  @param a  - Pointer to array
 *  @param n  - size of array
 *  @param op - Data type specific params 
		for operation such as compare and swap
 *  @return   - NA
 * */
void quick_sort(t_gen a, int n, t_dparams *op)
{
	int top, *stack, lo, hi, pivot; 

	// Create an auxiliary stack
	stack = (int*)get_mem(n, sizeof(int));

	// initialize top of stack
	top = -1;

	// push initial values of l and h to stack
	lo = 0;
	hi = n - 1;
	stack[++top] = lo;
	stack[++top] = hi;

	// Keep popping from stack while is not empty
	while (top >= 0) {
		// Pop h and l
		hi = stack[top--];
		lo = stack[top--];

		// Set pivot element at its correct position
		// in sorted array
		pivot = quick_sort_partition(a, lo, hi, op);

		// If there are elements on left side of pivot,
		// then push left side to stack
		if ((pivot - 1) > lo) {
			stack[++top] = lo;
			stack[++top] = pivot - 1;
		}

		// If there are elements on right side of pivot,
		// then push right side to stack
		if ((pivot + 1) < hi) {
			stack[++top] = pivot + 1;
			stack[++top] = hi;
		}
	}

	// free auxillary stack created
	free_mem(stack);
}

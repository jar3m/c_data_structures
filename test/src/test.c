/*! @file test.c
    @brief 
    Contains sample use cases/test of different data structure operations
*/

#include "common.h"
#include "link_list.h"
#include "stack.h"
#include "queue.h"

void test_stack();
void test_linklist();

/*! @brief  
 *   Main Driver test
 *  @param argc - Count cmd line arguments
 *  @param argv - Pointer to cmd line arguments
 *  @return 	- 0 on succesfull exit
 */
int main(int argc, char *argv[])
{
	size_t size = 0;
	int *ptr[100];
	int i ;	

	mem_init();
	logger_init();
	fault_manager_init(NULL);
	for (i = 0; i < 100; i ++) {
		ptr[i] = (int *)get_mem(1, sizeof(int));
		size += sizeof(*(ptr[i]));
	}
	printf("size of allocated memory = %lu\n" , size);
	for (i = 0; i < 100; i++) {
		free_mem(ptr[i]);
	}


	LOG_ERROR("COMMON", "Hello World\n");
	LOG_WARN("COMMON", "Hello World\n");		
	LOG_INFO("COMMON", "Hello World\n");		
	LOG_DEBUG("COMMON", "Hello World\n");		
	LOG_TRACE_IN("COMMON", "Hello World\n");
	LOG_TRACE_OUT("COMMON", "Hello World\n");

	test_linklist();
	test_stack();

	mem_finit();

	return 0;

}

/*! @brief  
 *   Test stack routines
 *  @return NA
 */
void test_stack()
{
	char c,*cp;
	float f,*fp;
	int *ip,i;
	t_dparams dp;
	t_stack *s1, *s2, *s3, *s4;

	
	init_data_params(&dp, eINT32);
	s1 = create_stack("Up Stack", 10, eARRAY_STACK, &dp);

	init_data_params(&dp, eINT8);
	s2 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, &dp);

	init_data_params(&dp, eFLOAT);
	s3 = create_stack("Down Stack", 10, eARRAY_STACK_DOWN, &dp);

	init_data_params(&dp, eFLOAT);
	s4 = create_stack("Up Stack LL", 10, eLL_STACK, &dp);

	for(i = 0; i < 10; i++) {
		s1->push(s1, assign_int(i));
		c= 'c' + i;
		s2->push(s2, assign_char(c));
		f= (float)i+0.222 / 2.0f;
		s3->push(s3, assign_float(f));
		s4->push(s4, assign_float(f));
	}
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);

	for(i = 0; i < 4; i++) {
		ip = s1->pop(s1);
		free_mem(ip);
		cp = s2->pop(s2);
		free_mem(cp);
		fp = s3->pop(s3);
		free_mem(fp);
		fp = s4->pop(s4);
		free_mem(fp);
	}
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);

	for(i = 4; i > 0; i--) {
		s1->push(s1, assign_int(i));
		c= 'c' + i;
		s2->push(s2, assign_int(c));
		f= (float)i+0.222 / 2.0f;
		s3->push(s3, assign_float(f));
		s4->push(s4, assign_float(f));
	}
	s1->print(s1);
	s2->print(s2);
	s3->print(s3);
	s4->print(s4);

	s1->destroy(s1);
	s2->destroy(s2);
	s3->destroy(s3);
	s4->destroy(s4);
}

/*! @brief  
 *   Test link list routines
 *  @return NA
 */
void test_linklist()
{
	char c,*cp,*sp,str[][64] = {"I", "See", "Everyting"};
	float f,*fp;
	int *ip, i;
	t_dparams dp;
	t_linklist *l1, *l2, *l3, *l4, *l5;

	init_data_params(&dp, eINT32);
	l1 = create_link_list("INT DLL",eDOUBLE_LINKLIST, &dp);

	init_data_params(&dp, eINT8);
	l2 = create_link_list("CHAR SLL",eSINGLE_LINKLIST, &dp);

	init_data_params(&dp, eFLOAT);
	l3 = create_link_list("FLOAT SCLL",eSINGLE_CIRCULAR_LINKLIST, &dp);

	init_data_params(&dp, eSTRING);
	l4 = create_link_list("STRING DCLL",eDOUBLE_CIRCULAR_LINKLIST, &dp);

	init_data_params(&dp, eFLOAT);
	l5 = create_link_list("FLOAT XORLL",eXOR_LINKLIST, &dp);

	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		l2->add(l2, assign_char(c));

		l1->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->add(l3, assign_float(f));
		l5->add(l5, assign_float(f));

		l4->add(l4, assign_string(str[i]));
	}
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	t_gen tmp;
	tmp =	l4->find(l4, "SEe");
  	if (tmp != NULL) {
		printf("Data present \n");
	}
	else {
		printf("Data not present \n");
	}
	
	LOG_INFO("TEST", "deleting nodes in link list\n");
	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		cp = l2->del(l2, &c);
		free_mem(cp);

		ip = l1->del(l1, &i);
		free_mem(ip);

		f= (float)i+0.222 / 2.0f;
		fp = l3->del(l3, &f);
		free_mem(fp);

		sp = l4->del(l4, &str[i]);
		free_mem(sp);

		fp = l5->del(l5, &f);
		free_mem(fp);
	}
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	for (i = 0; i < 3; i++) {
		c= 'c' + i;
		l2->append(l2, assign_char(c));

		l1->append(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->append(l3, assign_float(f));

		l4->append(l4, assign_string(str[i]));
		l5->append(l5, assign_float(f));
	}
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	for (i = 3; i < 13; i++) {
		c= 'c' + i;
		l2->add(l2, assign_char(c));

		l1->add(l1, assign_int(i));

		f= (float)i+0.222 / 2.0f;
		l3->add(l3, assign_float(f));
		l5->add(l5, assign_float(f));
	}
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	for (i = 2; i >= 0; i--) {
		cp = l2->del_idx(l2, i);
		free_mem(cp);

		ip = l1->del_idx(l1, i);
		free_mem(ip);

		fp = l3->del_idx(l3, i);
		free_mem(fp);

		sp = l4->del_idx(l4, i);
		free_mem(sp);
		
		fp = l5->del_idx(l5, i);
		free_mem(fp);
	}
	l1->print(l1);
	l2->print(l2);
	l3->print(l3);
	l4->print(l4);
	l5->print(l5);

	l1->destroy(l1);
	l2->destroy(l2);
	l3->destroy(l3);
	l4->destroy(l4);
	l5->destroy(l5);
}

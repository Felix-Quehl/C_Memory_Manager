#ifndef HEADER_TEST
#define HEADER_TEST


#define RUN_TEST(TEST) printf("%60s\t:", #TEST); TEST(); printf("\tPass\n")

void test_with_single_value_with_dedicated_release(void);
void test_with_single_value_with_generic_release(void);
void test_with_two_values_with_dedicated_release(void);
void test_with_two_values_with_dedicated_release_in_reverse(void);
void test_with_multiple_values_with_dedicated_release(void);
void test_with_external_allocated_pointer(void);
void test_that_no_leaks_remain(void);

#endif

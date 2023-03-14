#ifndef HEADER_TEST
#define HEADER_TEST


#define RUN_TEST(TEST) TEST(); printf("%s: success\n", #TEST)

void test_with_single_value_with_dedicated_release(void);
void test_with_single_value_with_generic_release(void);
void test_with_two_values_with_dedicated_release(void);
void test_with_two_values_with_dedicated_release_in_reverse(void);
void test_with_multiple_values_with_dedicated_release(void);
void test_that_no_leaks_remain(void);

#endif

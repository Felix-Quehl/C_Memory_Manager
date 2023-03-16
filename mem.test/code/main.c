#include <stdio.h>
#include <assert.h>
#include "mem.h"
#include "test.h"

int main()
{
    RUN_TEST(test_with_single_value_with_dedicated_release);
    RUN_TEST(test_with_single_value_with_generic_release);
    RUN_TEST(test_with_two_values_with_dedicated_release);
    RUN_TEST(test_with_two_values_with_dedicated_release_in_reverse);
    RUN_TEST(test_with_multiple_values_with_dedicated_release);
    RUN_TEST(test_with_external_allocated_pointer);
    RUN_TEST(test_that_no_leaks_remain);
    return 0;
}

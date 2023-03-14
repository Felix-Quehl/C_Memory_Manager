#include <stdio.h>
#include <assert.h>
#include "mem.h"
#include "boolean.h"

void assert_leak(short found_leak_excpected)
{

    short found_leak_actual = get_leak_flag();
    assert(found_leak_actual == found_leak_excpected);
    if (found_leak_actual)
    {
        prompt_memory_leaks();
    }
}

void test_with_single_value_with_dedicated_release()
{
    int *a = allocate_memory(sizeof(&a));
    assert_leak(TRUE);
    release_memory(a);
    assert_leak(FALSE);
}

void test_with_single_value_with_generic_release()
{
    int *a = allocate_memory(sizeof(&a));
    assert_leak(TRUE);
    release_all_memory();
    assert_leak(FALSE);
}

void test_with_two_values_with_dedicated_release()
{
    int *a = allocate_memory(sizeof(&a));
    assert_leak(TRUE);
    int *b = allocate_memory(sizeof(&b));
    assert_leak(TRUE);
    release_memory(a);
    assert_leak(TRUE);
    release_memory(b);
    assert_leak(FALSE);
}

void test_with_two_values_with_dedicated_release_in_reverse()
{
    int *a = allocate_memory(sizeof(&a));
    assert_leak(TRUE);
    int *b = allocate_memory(sizeof(&b));
    assert_leak(TRUE);
    release_memory(b);
    assert_leak(TRUE);
    release_memory(a);
    assert_leak(FALSE);
}

void test_with_multiple_values_with_dedicated_release()
{
    int *a = allocate_memory(sizeof(&a));
    assert_leak(TRUE);
    int *b = allocate_memory(sizeof(&b));
    assert_leak(TRUE);
    int *c = allocate_memory(sizeof(&c));
    assert_leak(TRUE);
    release_memory(b);
    assert_leak(TRUE);
    release_memory(a);
    assert_leak(TRUE);
    release_memory(c);
    assert_leak(FALSE);
}

int main()
{
    printf("*********************************************\n");
    test_with_single_value_with_dedicated_release();
    test_with_single_value_with_generic_release();
    test_with_two_values_with_dedicated_release();
    test_with_two_values_with_dedicated_release_in_reverse();
    test_with_multiple_values_with_dedicated_release();
    printf("*********************************************\n");
    assert_leak(FALSE);
    return 0;
}

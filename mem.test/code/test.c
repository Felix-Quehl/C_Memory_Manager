#include <stdio.h>
#include <assert.h>
#include "mem.h"
#include "test.h"

void test_with_single_value_with_dedicated_release()
{
    int *a;

    a = allocate_memory(sizeof(&a));
    assert(get_leak_flag() == 1);
    release_memory(a);
    assert(get_leak_flag() == 0);
}

void test_with_single_value_with_generic_release()
{
    int *a;

    a = allocate_memory(sizeof(&a));
    assert(get_leak_flag() == 1);
    release_all_memory();
    assert(get_leak_flag() == 0);
}

void test_with_two_values_with_dedicated_release()
{
    int *a;
    int *b;

    a = allocate_memory(sizeof(&a));
    assert(get_leak_flag() == 1);
    b = allocate_memory(sizeof(&b));
    assert(get_leak_flag() == 1);
    release_memory(a);
    assert(get_leak_flag() == 1);
    release_memory(b);
    assert(get_leak_flag() == 0);
}

void test_with_two_values_with_dedicated_release_in_reverse()
{
    int *a;
    int *b;

    a = allocate_memory(sizeof(&a));
    assert(get_leak_flag() == 1);
    b = allocate_memory(sizeof(&b));
    assert(get_leak_flag() == 1);
    release_memory(b);
    assert(get_leak_flag() == 1);
    release_memory(a);
    assert(get_leak_flag() == 0);
}

void test_with_multiple_values_with_dedicated_release()
{
    int *a;
    int *b;
    int *c;

    a = allocate_memory(sizeof(&a));
    assert(get_leak_flag() == 1);
    b = allocate_memory(sizeof(&b));
    assert(get_leak_flag() == 1);
    c = allocate_memory(sizeof(&c));
    assert(get_leak_flag() == 1);
    release_memory(b);
    assert(get_leak_flag() == 1);
    release_memory(a);
    assert(get_leak_flag() == 1);
    release_memory(c);
    assert(get_leak_flag() == 0);
}

void test_with_external_allocated_pointer()
{
    int *a;
    int *b;
    struct allocation_trace *trace;

    a = malloc(sizeof(&a));
    assert(get_leak_flag() == 0);
    b = allocate_memory(sizeof(&b));
    assert(get_leak_flag() == 1);
    trace = get_trace(a);
    assert(trace == NULL);
    release_memory(b);
    assert(get_leak_flag() == 0);
    release_memory(a);
}

void test_that_no_leaks_remain()
{
    assert(get_leak_flag() == 0);
}

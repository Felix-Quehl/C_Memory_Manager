#include <stdio.h>
#include "mem.h"

void main()
{

    printf("*****************************************\n");
    printf("checking at program entry:\n");
    assert_memoery_cleanup();
    printf("*****************************************\n");

    char *a = allocate_memory(25);
    char *c = malloc(123);
    release_memory(c);
    printf("checking after first allocation:\n");
    assert_memoery_cleanup();
    printf("*****************************************\n");

    char *b = allocate_memory(25);
    printf("checking after second allocation:\n");
    assert_memoery_cleanup();
    printf("*****************************************\n");

    release_memory(b);
    printf("checking after first release:\n");
    assert_memoery_cleanup();
    printf("*****************************************\n");

    release_all_memory();
    printf("checking release all:\n");
    assert_memoery_cleanup();
    printf("*****************************************\n");
}
#ifndef HEADER_MEM
#define HEADER_MEM

#include <stdlib.h>

struct allocation_trace
{
    struct allocation_trace *predecessor;
    struct allocation_trace *successor;
    void *memory_pointer;
    char *file;
    int line;
};

#define allocate_memory(amount) _allocate_memory(amount, __FILE__, __LINE__)
#define release_memory(pointer) _release_memory(pointer)

void *_allocate_memory(size_t amount, char *file, int line);
void _release_memory(void *pointer);
void release_all_memory();
void assert_memoery_cleanup();
#endif
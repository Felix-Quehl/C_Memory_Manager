#ifndef HEADER_MEM
#define HEADER_MEM

#include <stdlib.h>

#define allocate_memory(amount) _allocate_memory(amount, __FILE__, __LINE__)
#define release_memory(pointer) _release_memory(pointer)

struct allocation_trace
{
    struct allocation_trace *predecessor;
    struct allocation_trace *successor;
    void *memory_pointer;
    char *file;
    int line;
};

void _release_track(struct allocation_trace *trace);
struct allocation_trace *get_trace(void *pointer);
void *_allocate_memory(size_t amount, char *file, int line);
void _release_memory(void *pointer);
void release_all_memory();
void prompt_memory_leaks();
short get_leak_flag();

#endif

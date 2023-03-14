#ifndef HEADER_MEM
#define HEADER_MEM

#include <stdlib.h>

#define allocate_memory(amount) internal_allocate_memory(amount, __FILE__, __LINE__)

struct allocation_trace
{
    struct allocation_trace *predecessor;
    void *memory_pointer;
    struct allocation_trace *successor;
    char *file;
    long line;
    
};

void release_track(struct allocation_trace *trace);
struct allocation_trace *get_trace(void *pointer);
void *internal_allocate_memory(size_t amount, char *file, int line);
void release_memory(void *pointer);
void release_all_memory(void);
void prompt_memory_leaks(void);
short get_leak_flag(void);

#endif

#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "boolean.h"
#include "assert.h"

struct allocation_trace *root_trace;

void *_allocate_memory(size_t amount, char *file, int line)
{
    struct allocation_trace *new_trace = malloc(sizeof(struct allocation_trace));
    new_trace->file = file;
    new_trace->line = line;
    new_trace->memory_pointer = malloc(amount);

    if (root_trace == NULL)
    {
        /* make new trace self-refencing root trace */
        new_trace->successor = new_trace;
        new_trace->predecessor = new_trace;
        root_trace = new_trace;
    }
    else
    {
        /* set correct linking for new trace */
        new_trace->successor = root_trace;
        new_trace->predecessor = root_trace->predecessor;

        /* set correct linking existing traces */
        new_trace->successor->predecessor = new_trace;
        new_trace->predecessor->successor = new_trace;
    }

    return new_trace->memory_pointer;
}

void _release_memory(void *pointer)
{
    short reached_end = TRUE;
    short searching_for_trace;
    short trace_is_root;
    short there_are_other_traces;
    struct allocation_trace *trace = root_trace;
    assert(root_trace != NULL);
    do
    {
        searching_for_trace = trace->memory_pointer != pointer;
        if (searching_for_trace)
        {
            trace = trace->predecessor;
            reached_end = trace == root_trace;
            if (reached_end)
            {
                free(pointer);
                searching_for_trace = FALSE;
            }
        }
        else
        {
            trace_is_root = trace == root_trace;
            if (trace_is_root)
            {
                there_are_other_traces = trace != trace->successor;
                if (there_are_other_traces)
                {
                    root_trace = trace->successor;
                }
                else
                {
                    root_trace = NULL;
                }
            }
            trace->predecessor->successor = trace->successor;
            trace->successor->predecessor = trace->predecessor;
            free(trace->memory_pointer);
            free(trace);
        }
    } while (searching_for_trace);
}

void release_all_memory()
{
    while (root_trace != NULL)
    {
        _release_memory(root_trace->memory_pointer);
    }
}

void assert_memoery_cleanup()
{
    short not_reached_end = TRUE;
    if (root_trace != NULL)
    {
        struct allocation_trace *trace = root_trace;
        do
        {
            printf(
                "LEAK: memory address %p was allocated at '%s:%d' but not released\n",
                trace->memory_pointer,
                trace->file,
                trace->line);
            trace = trace->successor;
            not_reached_end = trace != root_trace;
        } while (not_reached_end);
    }
}

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

struct allocation_trace *get_trace(void *pointer)
{
    short reached_end = TRUE;
    short searching_for_trace;
    struct allocation_trace *trace = root_trace;
    if (get_leak_flag())
    {
        do
        {
            searching_for_trace = trace->memory_pointer != pointer;
            if (searching_for_trace)
            {
                trace = trace->predecessor;
                reached_end = trace == root_trace;
                if (reached_end)
                {
                    return NULL;
                }
            }
            else
            {
                return trace;
            }
        } while (searching_for_trace);
    }
    else
    {
        return NULL;
    }
}

void _release_memory(void *pointer)
{
    short trace_is_root;
    short there_are_other_traces;
    struct allocation_trace *trace = get_trace(pointer);
    _release_track(trace);
}

void _release_track(struct allocation_trace *trace)
{
    short trace_is_root;
    short there_are_other_traces;
    if (trace != NULL)
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
}

void release_all_memory()
{
    while (get_leak_flag())
    {
        _release_track(root_trace);
    }
}

short get_leak_flag()
{
    return root_trace != NULL;
}

void prompt_memory_leaks()
{
    short found_leak = get_leak_flag();
    if (found_leak)
    {
        short not_reached_end = TRUE;
        struct allocation_trace *trace = root_trace;
        do
        {
            printf(
                "memory address %p was allocated at '%s:%d' but not released\n",
                trace->memory_pointer,
                trace->file,
                trace->line);
            trace = trace->successor;
            not_reached_end = trace != root_trace;
        } while (not_reached_end);
    }
}

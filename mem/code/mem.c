#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

static struct allocation_trace *mem_trace_root;

void *internal_allocate_memory(size_t amount, char *file, int line)
{
    struct allocation_trace *new_trace;

    new_trace = malloc(sizeof(struct allocation_trace));
    new_trace->file = file;
    new_trace->line = line;
    new_trace->memory_pointer = malloc(amount);

    if (mem_trace_root == NULL)
    {
        /* make new trace self-referencing root trace */
        new_trace->successor = new_trace;
        new_trace->predecessor = new_trace;
        mem_trace_root = new_trace;
    }
    else
    {
        /* set correct linking for new trace */
        new_trace->successor = mem_trace_root;
        new_trace->predecessor = mem_trace_root->predecessor;

        /* set correct linking existing traces */
        new_trace->successor->predecessor = new_trace;
        new_trace->predecessor->successor = new_trace;
    }

    return new_trace->memory_pointer;
}

struct allocation_trace *get_trace(void *pointer)
{
    short searching_for_trace;
    short reached_end;
    struct allocation_trace *trace;

    trace = mem_trace_root;
    reached_end =1;
    if (get_leak_flag())
    {
        do
        {
            searching_for_trace = trace->memory_pointer != pointer;
            if (searching_for_trace)
            {
                trace = trace->predecessor;
                reached_end = trace == mem_trace_root;
                if (reached_end)
                {
                    break;
                }
            }
            else
            {
                return trace;
            }
        } while (searching_for_trace);
    }
    return NULL;
}

void release_memory(void *pointer)
{
    struct allocation_trace *trace;

    trace = get_trace(pointer);
    release_track(trace);
}

void release_track(struct allocation_trace *trace)
{
    short trace_is_root;
    short there_are_other_traces;

    if (trace != NULL)
    {
        trace_is_root = trace == mem_trace_root;
        if (trace_is_root)
        {
            there_are_other_traces = trace != trace->successor;
            if (there_are_other_traces)
            {
                mem_trace_root = trace->successor;
            }
            else
            {
                mem_trace_root = NULL;
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
        release_track(mem_trace_root);
    }
}

short get_leak_flag()
{
    return mem_trace_root != NULL;
}

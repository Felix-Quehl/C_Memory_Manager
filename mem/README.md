# Memory Manager Library

In a nutshell this code manages allocation and releasing of pointers for the consumer.
Its internals do use the system functions 'malloc' and 'free' to allocate and release pointers while also keeping inventory of them as a linked list.
Just use `make` to build it.

# Trace malloc and free in a c program 

This repo is a simple example how to trace if all pointer have been freed by wrapping malloc calls with meta logic that keeps track of pointers.

Sample Output:

```bash
*********************************************
memory address 0x5555555596e0 was allocated at './sources/main.c:19' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:27' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:35' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:35' but not released
memory address 0x555555559730 was allocated at './sources/main.c:37' but not released
memory address 0x555555559730 was allocated at './sources/main.c:37' but not released
memory address 0x555555559730 was allocated at './sources/main.c:47' but not released
memory address 0x555555559730 was allocated at './sources/main.c:47' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:49' but not released
memory address 0x555555559730 was allocated at './sources/main.c:47' but not released
memory address 0x555555559730 was allocated at './sources/main.c:59' but not released
memory address 0x555555559730 was allocated at './sources/main.c:59' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:61' but not released
memory address 0x555555559730 was allocated at './sources/main.c:59' but not released
memory address 0x5555555596e0 was allocated at './sources/main.c:61' but not released
memory address 0x555555559780 was allocated at './sources/main.c:63' but not released
memory address 0x555555559730 was allocated at './sources/main.c:59' but not released
memory address 0x555555559780 was allocated at './sources/main.c:63' but not released
memory address 0x555555559780 was allocated at './sources/main.c:63' but not released
*********************************************
```

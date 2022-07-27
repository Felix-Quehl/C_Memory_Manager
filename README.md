# Trace malloc and free in a c program 

This repo is a simple example how to trace if all pointer have been freed by wrapping malloc calls with meta logic that keeps track of pointers.

Sample Output:

```bash
*****************************************
checking at program entry:
*****************************************
checking after first allocation:
LEAK: memory address 0x5555555596e0 was allocated at './sources/main.c:12' but not released
*****************************************
checking after second allocation:
LEAK: memory address 0x5555555596e0 was allocated at './sources/main.c:12' but not released
LEAK: memory address 0x5555555597d0 was allocated at './sources/main.c:19' but not released
*****************************************
checking after first release:
LEAK: memory address 0x5555555596e0 was allocated at './sources/main.c:12' but not released
*****************************************
checking release all:
*****************************************
```

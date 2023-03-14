Pipeline Status: [![build_and_test](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml)

# C Memory Manager

This repo contain the code for a memory manager library in C.
The library help the consumer to keep track of memory allocations and detect memory leaks.

Please look at the unit test code to see how its used.

## How to Build and Test

Just use make to build and test everything.

```bash
make
```

Sample Output:

```
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make
clang -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories -I./header  -o code/mem.o -c code/mem.c 
clang --shared code/mem.o -o libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header  -o code/main.o -c code/main.c 
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header  -o code/test.o -c code/test.c 
clang -L../mem -lmem code/main.o code/test.o -o test.out
./mem.test/test.out 
Executing-Test: test_with_single_value_with_dedicated_release
Executing-Test: test_with_single_value_with_generic_release
Executing-Test: test_with_two_values_with_dedicated_release
Executing-Test: test_with_two_values_with_dedicated_release_in_reverse
Executing-Test: test_with_multiple_values_with_dedicated_release
Executing-Test: test_that_no_leaks_remain
```

After completion you can find the library file under this path: `./mem/libmem.so`

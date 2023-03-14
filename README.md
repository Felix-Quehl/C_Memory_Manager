# C Memory Manager

This repo contain the code for a memory manager library in C.
The library help the consumer to keep track of memory allocations and detect memory leaks.

Please look at the unit test code to see how its used.

## How to Build and Test

### Build

Just use make to build everything.

```bash
make
```

Sample Output:

```
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make && cp libmem.so ..
clang -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories -I./header  -o code/mem.o -c code/mem.c 
clang --shared code/mem.o -o libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make && cp test.out ..
clang -L../mem -lmem code/main.o code/test.o -o test.out
```

### Test

```bash
./test.out 
```

Sample Output:

```
test_with_single_value_with_dedicated_release: success
test_with_single_value_with_generic_release: success
test_with_two_values_with_dedicated_release: success
test_with_two_values_with_dedicated_release_in_reverse: success
test_with_multiple_values_with_dedicated_release: success
test_that_no_leaks_remain: success
```
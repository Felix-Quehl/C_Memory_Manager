
# C Memory Manager <br> [![build_and_test](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml)[![code_analysis](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/code_analysis.yml/badge.svg)](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/code_analysis.yml)

This repo contain the code for a **united-tested** memory manager library in C.
The library help the consumer to keep track of memory allocations and detect memory leaks.

Please look at the unit test code to see how its used.

## Build & Test

### Build

Use `make` top build a clean release version.

```bash
make clean release
```

Sample Output:

```bash
rm -fr libmem.so test.out libmem.so mem.h out
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make clean
rm -rf  libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make clean
rm -rf  test.out *.profraw *.profdata
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make 
clang -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories -I./header  -o code/mem.o -c code/mem.c 
clang --shared code/mem.o -o libmem.so
mkdir -p out
cp ./mem/libmem.so ./out
cp ./mem/header/mem.h ./out
```

After `make` completed the build completed , you can grab the dynamic linkable library file and the header file from the out directory: `./out`


### Test

Just use `make` to test everything.

```bash
make clean test
```

Sample Output:

```bash
rm -fr libmem.so test.out libmem.so mem.h out
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make clean
rm -rf .//code/mem.o libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make clean
rm -rf  test.out *.profraw *.profdata
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make debug
clang -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories -I./header -g -fprofile-instr-generate -fcoverage-mapping  -o code/mem.o -c code/mem.c 
clang --shared -fprofile-instr-generate -fcoverage-mapping code/mem.o -o libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make debug
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header -g -fprofile-instr-generate -fcoverage-mapping  -o code/main.o -c code/main.c 
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header -g -fprofile-instr-generate -fcoverage-mapping  -o code/test.o -c code/test.c 
clang -L../mem -lmem -fprofile-instr-generate -fcoverage-mapping code/main.o code/test.o -o test.out
./mem.test/test.out 
Executing-Test: test_with_single_value_with_dedicated_release
Executing-Test: test_with_single_value_with_generic_release
Executing-Test: test_with_two_values_with_dedicated_release
Executing-Test: test_with_two_values_with_dedicated_release_in_reverse
Executing-Test: test_with_multiple_values_with_dedicated_release
Executing-Test: test_that_no_leaks_remain
xcrun llvm-profdata merge -sparse ./mem.test/mem.profraw -o ./mem.test/mem.profdata
xcrun llvm-cov report ./mem/libmem.so -instr-profile=./mem.test/mem.profdata
Filename                                                      Regions    Missed Regions     Cover   Functions  Missed Functions  Executed       Lines      Missed Lines     Cover    Branches   Missed Branches     Cover
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/Users/felixquehl/Documents/c_trace_malloc/mem/code/mem.c          28                 2    92.86%           6                 0   100.00%          87                 4    95.40%          18                 4    77.78%
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TOTAL                                                              28                 2    92.86%           6                 0   100.00%          87                 4    95.40%          18                 4    77.78%
```

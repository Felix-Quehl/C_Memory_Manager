
# C Memory Manager <br> [![build_and_test](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/build_and_test.yml)[![code_analysis](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/code_analysis.yml/badge.svg)](https://github.com/Felix-Quehl/C_Memory_Manager/actions/workflows/code_analysis.yml)

This repo contains the code for a **united-tested** memory manager library in C.
The library helps the consumer to keep track of memory allocations and detect memory leaks.

Please look at the unit test code to see how it's used.

## Build & Test

### Build

Use `make` to build a clean release version.

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

After `make` completed the build completed, you can grab the dynamic linkable library file and the header file from the out directory: `./out`


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
rm -rf .//code/main.o .//code/test.o test.out *.profraw *.profdata
cd ./mem && /Applications/Xcode.app/Contents/Developer/usr/bin/make debug
clang -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories -I./header -g -fprofile-instr-generate -fcoverage-mapping  -o code/mem.o -c code/mem.c 
clang --shared -fprofile-instr-generate -fcoverage-mapping code/mem.o -o libmem.so
cd ./mem.test && /Applications/Xcode.app/Contents/Developer/usr/bin/make debug
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header -g -fprofile-instr-generate -fcoverage-mapping  -o code/main.o -c code/main.c 
clang -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories -I./header -I../mem/header -g -fprofile-instr-generate -fcoverage-mapping  -o code/test.o -c code/test.c 
clang -L../mem -lmem -fprofile-instr-generate -fcoverage-mapping code/main.o code/test.o -o test.out
./mem.test/test.out 
**************************************************

Testing:

               test_with_single_value_with_dedicated_release    :       Pass
                 test_with_single_value_with_generic_release    :       Pass
                 test_with_two_values_with_dedicated_release    :       Pass
      test_with_two_values_with_dedicated_release_in_reverse    :       Pass
            test_with_multiple_values_with_dedicated_release    :       Pass
                        test_with_external_allocated_pointer    :       Pass
                                   test_that_no_leaks_remain    :       Pass

**************************************************
xcrun llvm-profdata merge -sparse ./mem.test/mem.profraw -o ./mem.test/mem.profdata
xcrun llvm-cov export ./mem/libmem.so -instr-profile=./mem.test/mem.profdata | python3 ./.util/coverage_check.py 80
**************************************************

Coverage:

        branches        :       94.44%
        functions       :       100.00%
        instantiations  :       100.00%
        lines           :       100.00%
        regions         :       100.00%

**************************************************
```


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LLVM = llvm
endif
ifeq ($(UNAME_S),Darwin)
	LLVM = xcrun llvm
endif

all: release

release: ./mem/libmem.so out

test: args += debug
test: export LLVM_PROFILE_FILE=./mem.test/mem.profraw
test: export LD_LIBRARY_PATH=./mem
test: export DYLD_LIBRARY_PATH=./mem
test: ./mem/libmem.so ./mem.test/test.out
	./mem.test/test.out 
	$(LLVM)-profdata merge -sparse ./mem.test/mem.profraw -o ./mem.test/mem.profdata
	$(LLVM)-cov export ./mem/libmem.so -instr-profile=./mem.test/mem.profdata | python3 ./.util/coverage_check.py 80
	
out:
	mkdir -p out
	cp ./mem/*.so ./out
	cp ./mem/header/*.h ./out

./mem/libmem.so:
	cd ./mem && $(MAKE) $(args)

./mem.test/test.out:
	cd ./mem.test && $(MAKE) $(args)

	
clean:
	rm -fr libmem.so test.out libmem.so mem.h out
	cd ./mem && $(MAKE) clean
	cd ./mem.test && $(MAKE) clean
